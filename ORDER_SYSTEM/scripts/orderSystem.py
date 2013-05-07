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
import random

 
################################################################################################### 
#--------------------------------------- Variables ------------------------------------------------ 
################################################################################################### 
IP = '192.168.10.100'
port = 80
detectedBricks = [1,4,1]        # Red, Blue, Yellow (bricks)
base_url = 'http://192.168.10.100/'
bestOrder_dict = {0: {'orderName':0,'orderState':0,'orderDone':False, 'bricks':0,'ticket':0,'redTotal':0,'blueTotal':0,'yellowTotal':0,'redPicked':0,'bluePicked':0,'yellowPicked':0,'redNeeded':0,'blueNeeded':0,'yellowNeeded':0},        1: {'orderName':0,'orderDone':False, 'bricks':0,'ticket':0,'redTotal':0,'blueTotal':0,'yellowTotal':0,'redPicked':0,'bluePicked':0,'yellowPicked':0,'redNeeded':0,'blueNeeded':0,'yellowNeeded':0}}
slider = 1
################################################################################################### 
#------------------------------------- Helper functions ------------------------------------------- 
################################################################################################### 

def enum(**enums):
    return type('Enum', (), enums)
colors = enum(RED=0, BLUE=1, YELLOW=2)
 
def serverPath(path):
    return 'orders/' + path  

def printOrderSpecs(order):
    print "Name: " + str(order['orderName'])
    print "Done: " + str(order['orderDone'])
    print "Ticket: " + str(order['ticket']) 
    print "Red total: " + str(order['redTotal']) 
    print "Blue total: " + str(order['blueTotal'])
    print "Yellow total: " + str(order['yellowTotal'])
    print "Red picked: " + str(order['redPicked'])
    print "Blue picked: " + str(order['bluePicked']) 
    print "Yellow picked: " + str(order['yellowPicked'])


def printSliderSpecs(slider):
    print "Busy: " + str(slider['busy'])
    print "Order No: " + str(slider['order#'])
    print "Ticket: " + str(slider['ticket'])  
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
#--------------------------------------- Take order functions ------------------------------------- 
################################################################################################### 
            
def getOrders(numberOfOrders,detectedBricks):
    print '\n ################################ \t Requesting a list of ' + numberOfOrders + ' orders \t \t \t \t ##########################'
    orderList = requests.get(base_url + serverPath(numberOfOrders))
    orderNames = parseorderList(orderList.content)
    bricks = [0,0,0]
    bestOrder_dict['bricks'] = 0
    for x in range(0,int(numberOfOrders)):
        bestCounter = 0
        orderDetails = requests.get(base_url + serverPath(orderNames[x]))
        bricks[colors.RED] = int(parseorderDetails(orderDetails.content,'red'))
        bricks[colors.BLUE] = int(parseorderDetails(orderDetails.content,'blue'))
        bricks[colors.YELLOW] = int(parseorderDetails(orderDetails.content,'yellow'))
        print '\n ################################ \t Order ' + orderNames[x] + ' requires [RED BLUE YELLOW]: ' + '[' + str(bricks[colors.RED]) + ' ' + str(bricks[colors.BLUE]) + ' ' + str(bricks[colors.YELLOW]) + '] \t ##########################'
        #print orderDetails.content
        
        if((bricks[colors.RED] <= detectedBricks[colors.RED]) & (bricks[colors.BLUE] <= detectedBricks[colors.BLUE]) & (bricks[colors.YELLOW] <= detectedBricks[colors.YELLOW])):    # Every need can be fulfilled
            bestOrder_dict['redTotal'] = bricks[colors.RED]
            bestOrder_dict['blueTotal'] = bricks[colors.BLUE]
            bestOrder_dict['yellowTotal'] = bricks[colors.YELLOW]
            bestOrder_dict['redPicked'] = bestOrder_dict['redTotal']
            bestOrder_dict['bluePicked'] = bestOrder_dict['blueTotal']
            bestOrder_dict['yellowPicked'] = bestOrder_dict['yellowTotal']
            bestOrder_dict['orderName'] = orderNames[x]
            
            bestOrder_dict['redNeeded'] = bestOrder_dict['redTotal']-bestOrder_dict['redPicked']
            bestOrder_dict['blueNeeded'] = bestOrder_dict['blueTotal']-bestOrder_dict['bluePicked']
            bestOrder_dict['yellowNeeded'] = bestOrder_dict['yellowTotal']-bestOrder_dict['yellowPicked']
            
            orderReceipt = requests.put(base_url + serverPath(orderNames[x]))
            bestOrder_dict['ticket'] = parseOrderReceipt(orderReceipt.content)
            print '\n ################################ \t An optimal order was found: ' + orderNames[x] + ' with ticket: ' + bestOrder_dict['ticket'] + '\t ##################'
            bestOrder_dict['orderDone'] = True
            return bestOrder_dict
        else:
           
            if(bricks[colors.RED] != 0):
                diffRed = bricks[colors.RED]-detectedBricks[colors.RED]
                print "diffRed: " + str(diffRed) 
                if(diffRed < 0):
                    diffRed = abs(diffRed)
                    bestCounter += (detectedBricks[colors.RED]-diffRed)
                else:
                    bestCounter += bricks[colors.RED]-diffRed

            if(bricks[colors.BLUE] != 0):  
                diffBlue = bricks[colors.BLUE]-detectedBricks[colors.BLUE]
                print "diffBlue: " + str(diffBlue)
                if(diffBlue < 0):
                    diffBlue = abs(diffBlue)
                    bestCounter += (detectedBricks[colors.BLUE]-diffBlue)
                else:
                    bestCounter += bricks[colors.BLUE]-diffBlue
              
            if(bricks[colors.YELLOW] != 0):    
                diffYellow = bricks[colors.YELLOW]-detectedBricks[colors.YELLOW]
                print "diffYellow: " + str(diffYellow)
                if(diffYellow < 0):
                    diffYellow = abs(diffYellow)
                    bestCounter += (detectedBricks[colors.YELLOW]-diffYellow)
                else:
                    bestCounter += bricks[colors.YELLOW]-diffYellow
             
            print "bestCounter: " + str(bestCounter)
            print "bestOrder Bricks: " + str(bestOrder_dict['bricks'])
            if(bestCounter > bestOrder_dict['bricks']):
                bestOrder_dict['bricks'] = bestCounter
                bestOrder_dict['redTotal'] = bricks[colors.RED]
                bestOrder_dict['blueTotal'] = bricks[colors.BLUE]
                bestOrder_dict['yellowTotal'] = bricks[colors.YELLOW]
                bestOrder_dict['orderName'] = orderNames[x]
                
                if(bestOrder_dict['redTotal'] <= detectedBricks[colors.RED]):
                    bestOrder_dict['redPicked'] = bricks[colors.RED]
                if(bestOrder_dict['redTotal'] > detectedBricks[colors.RED]):
                    bestOrder_dict['redPicked'] = detectedBricks[colors.RED]
                    
                if(bestOrder_dict['blueTotal'] <= detectedBricks[colors.BLUE]):
                    bestOrder_dict['bluePicked'] = bricks[colors.BLUE]
                if(bestOrder_dict['blueTotal'] > detectedBricks[colors.BLUE]):
                    bestOrder_dict['bluePicked'] = detectedBricks[colors.BLUE]
                    
                if(bestOrder_dict['yellowTotal'] <= detectedBricks[colors.YELLOW]):
                    bestOrder_dict['yellowPicked'] = bricks[colors.YELLOW]
                if(bestOrder_dict['yellowTotal'] > detectedBricks[colors.YELLOW]):
                    bestOrder_dict['yellowPicked'] = detectedBricks[colors.YELLOW]    
                
            bestOrder_dict['redNeeded'] = bestOrder_dict['redTotal']-bestOrder_dict['redPicked']
            bestOrder_dict['blueNeeded'] = bestOrder_dict['blueTotal']-bestOrder_dict['bluePicked']
            bestOrder_dict['yellowNeeded'] = bestOrder_dict['yellowTotal']-bestOrder_dict['yellowPicked']
                 
    orderReceipt = requests.put(base_url + serverPath(bestOrder_dict['orderName']))
    print orderReceipt.url
    print orderReceipt.content
    bestOrder_dict['ticket'] = parseOrderReceipt(orderReceipt.content)
    bestOrder_dict['orderDone'] = False
    print '\n ################################ \t An order was found: ' + str(bestOrder_dict['orderName']) + ' with ticket: ' + str(bestOrder_dict['ticket']) + '\t ##########################'
    return bestOrder_dict


def getSpecificOrder(prevOrderDetails,detectedBricks):
    print '\n ################################ \t Continued processing order: ' + bestOrder_dict['orderName'] + '\t ##########################'
    bricks = [0,0,0]
    bricks[colors.RED] = prevOrderDetails['redTotal'] - prevOrderDetails['redPicked']       # We subtract the bricks that have already been picked up in the previous batch
    if bricks[colors.RED] < 0:                      # Clamping
        bricks[colors.RED] = 0
    bricks[colors.BLUE] = prevOrderDetails['blueTotal'] - prevOrderDetails['bluePicked']
    if bricks[colors.BLUE] < 0:
        bricks[colors.BLUE] = 0
    bricks[colors.YELLOW] = prevOrderDetails['yellowTotal'] - prevOrderDetails['yellowPicked']
    if bricks[colors.YELLOW] < 0:
        bricks[colors.YELLOW] = 0
        
    if((bricks[colors.RED] <= detectedBricks[colors.RED]) & (bricks[colors.BLUE] <= detectedBricks[colors.BLUE]) & (bricks[colors.YELLOW] <= detectedBricks[colors.YELLOW])):    # Every need can be fulfilled
        bestOrder_dict['redPicked'] = bestOrder_dict['redTotal']
        bestOrder_dict['bluePicked'] = bestOrder_dict['blueTotal']
        bestOrder_dict['yellowPicked'] = bestOrder_dict['yellowTotal']
        bestOrder_dict['orderName'] = prevOrderDetails['orderName']
        print '\n ################################ \t Finished order: ' + str(prevOrderDetails['orderName']) + ' with ticket: ' + str(prevOrderDetails['ticket']) + '\t ##################'
        bestOrder_dict['orderDone'] = True
        return bestOrder_dict
    else:
        if(bricks[colors.RED] <= detectedBricks[colors.RED]):       # If we have detected enough or more red bricks than the order requests
            bestOrder_dict['red'] = bricks[colors.RED]
         
        if(bricks[colors.BLUE] <= detectedBricks[colors.BLUE]):
            bestOrder_dict['blue'] = bricks[colors.BLUE]
         
        if(bricks[colors.YELLOW] <= detectedBricks[colors.YELLOW]):
            bestOrder_dict['yellow'] = bricks[colors.YELLOW]
            
        if(bestOrder_dict['redNeeded'] <= detectedBricks[colors.RED]):
            bestOrder_dict['redPicked'] = bricks[colors.RED]
        if(bestOrder_dict['redNeeded'] > detectedBricks[colors.RED]):
            bestOrder_dict['redPicked'] = detectedBricks[colors.RED]
            
        if(bestOrder_dict['blueNeeded'] <= detectedBricks[colors.BLUE]):
            bestOrder_dict['bluePicked'] = bricks[colors.BLUE]
        if(bestOrder_dict['blueNeeded'] > detectedBricks[colors.BLUE]):
            bestOrder_dict['bluePicked'] = detectedBricks[colors.BLUE]
            
        if(bestOrder_dict['yellowNeeded'] <= detectedBricks[colors.YELLOW]):
            bestOrder_dict['yellowPicked'] = bricks[colors.YELLOW]
        if(bestOrder_dict['yellowNeeded'] > detectedBricks[colors.YELLOW]):
            bestOrder_dict['yellowPicked'] = detectedBricks[colors.YELLOW]    
        
        bestOrder_dict['redNeeded'] -= bestOrder_dict['redPicked']
        bestOrder_dict['blueNeeded'] -= bestOrder_dict['bluePicked'] 
        bestOrder_dict['yellowNeeded'] -= bestOrder_dict['yellowPicked']
        
        if(bestOrder_dict['redNeeded'] == 0 and bestOrder_dict['blueNeeded'] == 0 and bestOrder_dict['yellowNeeded'] == 0):
            bestOrder_dict['orderDone'] = True
        else:
            bestOrder_dict['orderDone'] = False
        
    return bestOrder_dict
    
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
    if(int(RESTlog.status_code) == 201):
        print '\n ################################ \t Log successfully sent: \t ################################################## \nEvent: ' + event + '\nComment: ' + comment + '\n###########################################################################################################################'
    
    return log




################################################################################################### 
#--------------------------------------- ROS functions -------------------------------------------- 
################################################################################################### 


def publish(bestOrder):

    pub_msg = order()
    pub_msg.header.stamp = rospy.get_rostime()
    pub_msg.red = bestOrder['redTotal']
    pub_msg.blue = bestOrder['blueTotal']
    pub_msg.yellow = bestOrder['yellowTotal']
    pub_msg.ticket = str(bestOrder['ticket'])
    global pub
    pub.publish(pub_msg)
    


################################################################################################### 
#--------------------------------------- Main program --------------------------------------------- 
################################################################################################### 

def visCallback(data):
    detectedBricks[colors.RED] = data.red
    detectedBricks[colors.BLUE] = data.blue
    detectedBricks[colors.YELLOW] = data.yellow

################################################################################################### 
#--------------------------------------- Main function -------------------------------------------- 
###################################################################################################     

def main():
    rospy.init_node('orderSystem')
    listReceived = True
    requestedOrders = '5'
    global bestOrder
    global slider
    global sliderStatus
    sliderStatus = dict(bestOrder_dict)
    bestOrder = dict(bestOrder_dict)
    bestOrder[0]['orderState'] = "IDLE"
    bestOrder[1]['orderState'] = "IDLE"
    while not rospy.is_shutdown():
        slider = not slider
        global detectedBricks
        print '\n ################################ \t Slider 0 \t \t ##########################'
        printOrderSpecs(sliderStatus[0])
        print '\n ################################ \t Slider 1 \t \t ##########################'
        printOrderSpecs(sliderStatus[1])
################################################################################################### 
#--------------------------------------- Idle state -----------------------------------------------
###################################################################################################         
        if (bestOrder[slider]['orderState'] == "IDLE"):
            if(listReceived == True):
            
                print '\n ################################ \t Detected bricks [RED BLUE YELLOW]: [' +  str(detectedBricks[colors.RED]) + ' ' + str(detectedBricks[colors.BLUE]) + ' ' + str(detectedBricks[colors.YELLOW]) + '] \t \t ##########################'
                bestOrder[slider]['orderState'] = "GET_ORDER"
                
                rospy.sleep(1.0)
            else:
                print "Waiting for Vision input"
                listReceived=True       # Simulating Vision input
                rospy.sleep(3.0)
                
################################################################################################### 
#--------------------------------------- Get order state ------------------------------------------ 
###################################################################################################                
        if(bestOrder[slider]['orderState'] =="GET_ORDER"):
            bestOrder[slider] = getOrders(requestedOrders, detectedBricks)   
            printOrderSpecs(bestOrder[slider])
            sliderStatus[slider] = bestOrder[slider]
            
            publish(bestOrder[slider])
            rospy.sleep(1.0)
                
        if bestOrder[slider]['orderDone'] == True:
            bestOrder[slider]['orderState'] = "ORDER_DONE"
        else:
            bestOrder[slider]['orderState'] = "ORDER_NOT_DONE"
            
################################################################################################### 
#--------------------------------------- Order done state ----------------------------------------- 
###################################################################################################              
        if(bestOrder[slider]['orderState'] =="ORDER_DONE"):
            #deleteOrder(bestOrder[slider]['orderName'],bestOrder[slider]['ticket'] )
            sliderStatus = dict(bestOrder_dict)     # Clearing the slider status (the slider is now available)
            logMsg('COMPLETED', bestOrder[slider]['orderName'])
            # Signal Vision system that the order is done. Wait for new detectedBricks
            bestOrder[slider]['orderDone'] = False
            bestOrder[slider]['orderState'] = "IDLE"
            
            rospy.sleep(1.0)
            
################################################################################################### 
#--------------------------------------- Order not done state ------------------------------------- 
###################################################################################################        
        if(bestOrder[slider]['orderState'] == "ORDER_NOT_DONE"):        
            detectedBricks = [random.randrange(0, 5),random.randrange(0, 5),random.randrange(0, 5)]
            print '\n ################################ \t New detected bricks [RED BLUE YELLOW]: [ ' + str(detectedBricks[0]), str(detectedBricks[1]), str(detectedBricks[2]) + '] \t \t ##########################'
            bestOrder[slider] = getSpecificOrder(bestOrder[slider],detectedBricks)
            
            printOrderSpecs(bestOrder[slider])          
                
            publish(bestOrder[slider])
            
            if bestOrder[slider]['orderDone'] == True:
                bestOrder[slider]['orderState'] = "ORDER_DONE"
            else:
                bestOrder[slider]['orderState'] = "ORDER_NOT_DONE"
                  
            rospy.sleep(1.0)

################################################################################################### 
#--------------------------------------- ROS topic I/O -------------------------------------------- 
###################################################################################################

if __name__ == '__main__':
   pub = rospy.Publisher('chosenOrder', order)
   rospy.Subscriber("visDetected", order, visCallback)
   main()
