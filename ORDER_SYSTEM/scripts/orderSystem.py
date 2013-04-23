#!/usr/bin/env python
#import socket   #for sockets
import roslib; roslib.load_manifest('ORDER_SYSTEM')
import rospy
from MESSAGES.msg import order

import sys                              #for exit
import xml.etree.ElementTree as xml     # XML parsing
import requests                         # REST/HTML requests
from time import gmtime, strftime       # Get current time
import shutil                           # file I/O
from lxml import etree

 
################################################################################################### 
#--------------------------------------- Variables ------------------------------------------------ 
################################################################################################### 
IP = '192.168.10.100'
port = 80 
detectedBricks = [0,1,3]        # Red, Blue, Yellow (bricks)
base_url = 'http://192.168.10.100/'

################################################################################################### 
#------------------------------------- Helper functions ------------------------------------------- 
################################################################################################### 

def enum(**enums):
    return type('Enum', (), enums)
colors = enum(RED=0, BLUE=1, YELLOW=2)
 
def serverPath(path):
    return 'orders/' + path  
  
################################################################################################### 
#------------------------------------ Parsing functions ------------------------------------------- 
################################################################################################### 
  
def parseorderList(data):
    tree = xml.fromstring(data)
    outputList = []
    for index in tree.iter('order'):
        #print index.text[index.text.find('ord_'):]
        outputList.append(index.text[index.text.find('ord_'):])
    return outputList

def parseorderDetails(data,brickColor):
    tree = xml.fromstring(data)
    for index in tree.iter(brickColor):
        return index.text

def parseOrderReceipt(data):
    tree = xml.fromstring(data)
    return tree.text
    
################################################################################################### 
#--------------------------------------- Take order function -------------------------------------- 
################################################################################################### 
            
def getOrders(numberOfOrders,detectedBricks):
    print '\n ################################ \t Requesting a list of ' + numberOfOrders + ' orders \t \t \t \t ##########################'
    orderList = requests.get(base_url + serverPath(numberOfOrders))
    orderNames = parseorderList(orderList.content)
    bestOrder = [0,0,0]
    bricks = [0,0,0]
    bestCounter = 0
    bestOrder_dict = {'order#':0, 'bricks':0} 
    for x in range(0,int(numberOfOrders)):
        orderDetails = requests.get(base_url + serverPath(str(orderNames[x])))
        bricks[colors.RED] = int(parseorderDetails(orderDetails.content,'red'))
        bricks[colors.BLUE] = int(parseorderDetails(orderDetails.content,'blue'))
        bricks[colors.YELLOW] = int(parseorderDetails(orderDetails.content,'yellow'))
        print '\n ################################ \t Order ' + orderNames[x] + ' requires [RED BLUE YELLOW]: ' + '[' + str(bricks[colors.RED]) + ' ' + str(bricks[colors.BLUE]) + ' ' + str(bricks[colors.YELLOW]) + '] \t ##########################'
        #print orderDetails.content
        if((bricks[colors.RED] <= detectedBricks[colors.RED]) & (bricks[colors.BLUE] <= detectedBricks[colors.BLUE]) & (bricks[colors.YELLOW] <= detectedBricks[colors.YELLOW])):    # Every need can be fulfilled
            bestOrder = bricks
            orderReceipt = requests.put(base_url + serverPath(orderNames[x]))
            print '\n ################################ \t An optimal order was found: ' + orderNames[x] + ' with ticket: ' + parseOrderReceipt(orderReceipt.content) + '\t ##################'
            return bestOrder
        else:
            if(bricks[colors.RED] <= detectedBricks[colors.RED]):       # If we have detected enough or more red bricks than the order requests
                bestCounter += bricks[colors.RED]
                bestOrder[colors.RED] = bricks[colors.RED]
             
            if(bricks[colors.BLUE] <= detectedBricks[colors.BLUE]):
                bestCounter += bricks[colors.BLUE]
                bestOrder[colors.BLUE] = bricks[colors.BLUE]
             
            if(bricks[colors.YELLOW] <= detectedBricks[colors.YELLOW]):
                bestCounter += bricks[colors.YELLOW]
                bestOrder[colors.YELLOW] = bricks[colors.YELLOW]
             
            if(bestCounter > bestOrder_dict['bricks']):
                bestOrder_dict['bricks'] = bestCounter
                bestOrder_dict['order#'] = orderNames[x]
                 
    orderReceipt = requests.put(base_url + serverPath(bestOrder_dict['order#']))
    print '\n ################################ \t An order was found: ' + bestOrder_dict['order#'] + ' with ticket: ' + parseOrderReceipt(orderReceipt.content) + '\t ##########################'
    return bestOrder
 
################################################################################################### 
#--------------------------------------- Delete order function ------------------------------------ 
###################################################################################################  
def deleteOrder(orderName, ticket):
    path = orderName + '/' + ticket
    status = requests.delete(base_url + serverPath(path))
    #print status.url, status.status_code
    if(int(status.status_code) == 200):
        print '\n ################################ \t Order ' + orderName + ' with ticket ' + ticket + ' successfully deleted \t ##################'
    else:
        print '\n ################################ \t Order ' + orderName + ' with ticket ' + ticket + ' could NOT be deleted \t ##################'
                


################################################################################################### 
#--------------------------------------- Logging function ---------------------------------------- 
###################################################################################################  

def logMsg(event, comment):
    top = etree.Element('log_entry')
    
    #comment = xml.Comment('Generated for PyMOTW')
    #top.append(comment)
    
    childEvent = etree.SubElement(top, 'event')
    childEvent.text = event
    
    childTime = etree.SubElement(top, 'time')
    childTime.text = strftime("%Y-%m-%d %H:%M:%S")
    
    childCellID = etree.SubElement(top, 'cell_id')
    childCellID.text = '9'
    
    childComment = etree.SubElement(top, 'comment')
    childComment.text = comment
    
    log = etree.tostring(top,encoding='utf-8',xml_declaration=True,pretty_print=True)
    RESTlog = requests.post(base_url + 'log', data=log)
    #print log
    if(int(RESTlog.status_code) == 201):
        print '\n ################################ \t Log successfully sent: \t ################################################## \nEvent: ' + event + '\nComment: ' + comment + '\n###########################################################################################################################'
    
    return log

def publish(bestOrder):
    pub_msg = order()
    pub_msg.header.stamp = rospy.get_rostime()
    pub_msg.red = bestOrder[0]
    pub_msg.blue = bestOrder[1]
    pub_msg.yellow = bestOrder[2]
    global pub
    pub.publish(pub_msg)

################################################################################################### 
#--------------------------------------- Main program --------------------------------------------- 
################################################################################################### 
def main():
    rospy.init_node('orderSystem')
    listReceived = True
    
    while not rospy.is_shutdown():
        if (listReceived==True):
            requestedOrders = '5'
            orderList = requests.get(base_url + serverPath(requestedOrders))
            #print orderList.content
            bestOrder=getOrders(requestedOrders, detectedBricks)
            #deleteOrder('ord_00030', 'ord_OG4252')
            #logMsg('test', 'some_order')
            publish(bestOrder)
            listReceived=False
            rospy.sleep(1.0)
        
    





if __name__ == '__main__':
   pub = rospy.Publisher('chosenOrder', order)
   main()
