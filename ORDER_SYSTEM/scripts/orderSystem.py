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
import warnings

 
################################################################################################### 
#--------------------------------------- Variables ------------------------------------------------ 
################################################################################################### 
IP = '192.168.10.100'
port = 80
detectedBricks = [2,2,2]        # Red, Blue, Yellow (bricks)
base_url = 'http://192.168.10.100/'
bestOrder_dict = {0: {'orderName':'None','orderState':"IDLE",'orderDone':True,'slider':3, 'bricks':0,'ticket':0,'redTotal':0,'blueTotal':0,'yellowTotal':0,'redPicked':0,'bluePicked':0,'yellowPicked':0,'redNeeded':0,'blueNeeded':0,'yellowNeeded':0},        1: {'orderName':'None','orderState':"IDLE",'orderDone':True,'slider':3, 'bricks':0,'ticket':0,'redTotal':0,'blueTotal':0,'yellowTotal':0,'redPicked':0,'bluePicked':0,'yellowPicked':0,'redNeeded':0,'blueNeeded':0,'yellowNeeded':0}}
slider_dict = {0:{'busy':False,'orderName':'None'}, 1:{'busy':False,'orderName':'None'}}
orderProcess = True
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
    print "Order state: " + str(order['orderState'])
    print "Ticket: " + str(order['ticket']) 
    print "Red total: " + str(order['redTotal']) 
    print "Blue total: " + str(order['blueTotal'])
    print "Yellow total: " + str(order['yellowTotal'])
    print "Red picked: " + str(order['redPicked'])
    print "Blue picked: " + str(order['bluePicked']) 
    print "Yellow picked: " + str(order['yellowPicked'])
    print "Red Needed:" + str(order['redNeeded'])
    print "Blue Needed:" + str(order['blueNeeded'])
    print "Yellow Needed:" + str(order['yellowNeeded'])
    

def printSliderStatus(sliderStatus):
    print "Slider busy: " + str(sliderStatus['busy'])
    print "Slider Order name: " + str(sliderStatus['orderName']) 

def BricksDetected():
    if(detectedBricks[colors.RED]!= 0 and detectedBricks[colors.BLUE]!= 0 and detectedBricks[colors.YELLOW]!= 0):
        return True
    else:
        return False
    
    
def resetSlider(bestOrder,sliderStatus):
    sliderStatus[orderProcess]['busy'] = False
    sliderStatus[orderProcess]['orderName'] = 'None'
    bestOrder[orderProcess]['slider'] = 3     
    
    
def assignSlider(bestOrder,sliderStatus):
    if(sliderStatus[0]['busy'] == False):
        sliderStatus[0]['busy'] = True
        sliderStatus[0]['orderName'] = bestOrder['orderName']
        bestOrder['slider'] = 0
    elif(sliderStatus[1]['busy'] == False):
        sliderStatus[1]['busy'] = True
        sliderStatus[1]['orderName'] = bestOrder['orderName']
        bestOrder['slider'] = 1     
 
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
            
def getOrders(numberOfOrders,detectedBricks,orderProcess):
    print '\n ################################ \t Requesting a list of ' + numberOfOrders + ' orders \t \t \t \t ##########################'
    #===========================================================================
    # try:
    #===========================================================================
    orderList = requests.get(base_url + serverPath(numberOfOrders))
    #===========================================================================
    #     if(orderList.statuscode != 200):
    #         print 'HTTP error: Bad request'
    #     return 0
    #     except Exception, err:
    #         print "ERROR: Connection error (you're on eduroam, you fool!)"
    #         sys.exit()
    #===========================================================================
    orderNames = parseorderList(orderList.content)
    bricks = [0,0,0]
    bestOrder_dict['bricks'] = 0
    for x in range(0,int(numberOfOrders)):
        bestCounter = 0
        orderDetails = requests.get(base_url + serverPath(orderNames[x]))
        bricks[colors.RED] = int(parseorderDetails(orderDetails.content,'red'))
        bricks[colors.BLUE] = int(parseorderDetails(orderDetails.content,'blue'))
        bricks[colors.YELLOW] = int(parseorderDetails(orderDetails.content,'yellow'))
        bestOrder_dict['orderName'] = orderNames[x]
        print '\n ################################ \t Order ' + orderNames[x] + ' requires [RED BLUE YELLOW]: ' + '[' + str(bricks[colors.RED]) + ' ' + str(bricks[colors.BLUE]) + ' ' + str(bricks[colors.YELLOW]) + '] \t ##########################'
        #print orderDetails.content
        
        bestOrder_dict['redTotal'] = bricks[colors.RED]
        bestOrder_dict['blueTotal'] = bricks[colors.BLUE]
        bestOrder_dict['yellowTotal'] = bricks[colors.YELLOW]
        
        if((bricks[colors.RED] <= detectedBricks[colors.RED]) & (bricks[colors.BLUE] <= detectedBricks[colors.BLUE]) & (bricks[colors.YELLOW] <= detectedBricks[colors.YELLOW])):    # Every need can be fulfilled
            bestOrder_dict['redPicked'] = bestOrder_dict['redTotal']
            bestOrder_dict['bluePicked'] = bestOrder_dict['blueTotal']
            bestOrder_dict['yellowPicked'] = bestOrder_dict['yellowTotal']
            
            bestOrder_dict['redNeeded'] = bestOrder_dict['redTotal']-bestOrder_dict['redPicked']
            bestOrder_dict['blueNeeded'] = bestOrder_dict['blueTotal']-bestOrder_dict['bluePicked']
            bestOrder_dict['yellowNeeded'] = bestOrder_dict['yellowTotal']-bestOrder_dict['yellowPicked']
            
            orderReceipt = requests.put(base_url + serverPath(orderNames[x]))
            bestOrder_dict['ticket'] = parseOrderReceipt(orderReceipt.content)
            print '\n ################################ \t An optimal order was found: ' + orderNames[x] + ' with ticket: ' + bestOrder_dict['ticket'] + '\t ##################'
            bestOrder_dict['orderState'] = "ORDER_DONE"
            return bestOrder_dict
        else:
           
            diffRed = bricks[colors.RED]-detectedBricks[colors.RED]
            if(diffRed < 0):
                diffRed = abs(diffRed)
                bestCounter += (detectedBricks[colors.RED]-diffRed)
            else:
                bestCounter += bricks[colors.RED]-diffRed

            diffBlue = bricks[colors.BLUE]-detectedBricks[colors.BLUE]
            if(diffBlue < 0):
                diffBlue = abs(diffBlue)
                bestCounter += (detectedBricks[colors.BLUE]-diffBlue)
            else:
                bestCounter += bricks[colors.BLUE]-diffBlue
           
            diffYellow = bricks[colors.YELLOW]-detectedBricks[colors.YELLOW]
            if(diffYellow < 0):
                diffYellow = abs(diffYellow)
                bestCounter += (detectedBricks[colors.YELLOW]-diffYellow)
            else:
                bestCounter += bricks[colors.YELLOW]-diffYellow
            
            print 'bestCounter: ' + str(bestCounter)
            print 'bricks: ' + str(bestOrder_dict['bricks'])           
            if(bestCounter > bestOrder_dict['bricks']):
                bestOrder_dict['bricks'] = bestCounter
                
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
    bestOrder_dict['orderState'] = "ORDER_NOT_DONE"
    
    print '\n ################################ \t An order was found: ' + str(bestOrder_dict['orderName']) + ' with ticket: ' + str(bestOrder_dict['ticket']) + '\t ##########################'
    return bestOrder_dict


def getSpecificOrder(prevOrderDetails,detectedBricks,orderProcess):
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
        bestOrder_dict['orderState'] = "ORDER_DONE"
        return bestOrder_dict
    else:
         
        if(bestOrder_dict['redPicked'] != prevOrderDetails['redPicked']): 
            if(bestOrder_dict['redNeeded'] <= detectedBricks[colors.RED]):
                bestOrder_dict['redPicked'] = bricks[colors.RED]
            if(bestOrder_dict['redNeeded'] > detectedBricks[colors.RED]):
                bestOrder_dict['redPicked'] = detectedBricks[colors.RED]
        
        if(bestOrder_dict['bluePicked'] != prevOrderDetails['bluePicked']):      
            if(bestOrder_dict['blueNeeded'] <= detectedBricks[colors.BLUE]):
                bestOrder_dict['bluePicked'] = bricks[colors.BLUE]
            if(bestOrder_dict['blueNeeded'] > detectedBricks[colors.BLUE]):
                bestOrder_dict['bluePicked'] = detectedBricks[colors.BLUE]
        
        if(bestOrder_dict['yellowPicked'] != prevOrderDetails['yellowPicked']):         
            if(bestOrder_dict['yellowNeeded'] <= detectedBricks[colors.YELLOW]):
                bestOrder_dict['yellowPicked'] = bricks[colors.YELLOW]
            if(bestOrder_dict['yellowNeeded'] > detectedBricks[colors.YELLOW]):
                bestOrder_dict['yellowPicked'] = detectedBricks[colors.YELLOW]
                
        if(bestOrder_dict['redPicked'] != prevOrderDetails['redPicked']):  
            bestOrder_dict['redNeeded'] -= bestOrder_dict['redPicked']
            
        if(bestOrder_dict['bluePicked'] != prevOrderDetails['bluePicked']):      
            bestOrder_dict['blueNeeded'] -= bestOrder_dict['bluePicked']
            
        if(bestOrder_dict['yellowPicked'] != prevOrderDetails['yellowPicked']):       
            bestOrder_dict['yellowNeeded'] -= bestOrder_dict['yellowPicked']
        
        if(bestOrder_dict['redNeeded'] == 0 and bestOrder_dict['blueNeeded'] == 0 and bestOrder_dict['yellowNeeded'] == 0):
            bestOrder_dict['orderState'] = "ORDER_DONE"
        else:
            bestOrder_dict['orderState'] = "ORDER_NOT_DONE"
        
    
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
    pub_msg.red = bestOrder['redNeeded']
    pub_msg.blue = bestOrder['blueNeeded']
    pub_msg.yellow = bestOrder['yellowNeeded']
    pub_msg.slider = bestOrder['slider']
    global pub
    pub.publish(pub_msg)
    


################################################################################################### 
#--------------------------------------- Main program --------------------------------------------- 
################################################################################################### 

def visCallback(data):
    print "NEW BRICKS DETECTED!!!"
    #listReceived = True
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
    global ongoingOrder
    global orderProcess
    global sliderStatus
    sliderStatus = dict(slider_dict)
    bestOrder = dict(bestOrder_dict)
    ongoingOrder = dict(bestOrder_dict)
    rospy.sleep(2.0)
    while not rospy.is_shutdown():
        global detectedBricks
        try:
            while (detectedBricks[colors.RED]== 0 and detectedBricks[colors.BLUE]== 0 and detectedBricks[colors.YELLOW]== 0):
                print  '\n ################################ \t Waiting for detected bricks \t \t ##########################'
                detectedBricks = [random.randrange(0, 2),random.randrange(0, 2),random.randrange(0, 2)]
                rospy.sleep(3.0)
        except KeyboardInterrupt:
            sys.exit()  

        orderProcess = not orderProcess

################################################################################################### 
#--------------------------------------- Idle state -----------------------------------------------
###################################################################################################         
        if (bestOrder[orderProcess]['orderState'] == "IDLE"):
            if(listReceived == True):
            
                print '\n ################################ \t Detected bricks [RED BLUE YELLOW]: [' +  str(detectedBricks[colors.RED]) + ' ' + str(detectedBricks[colors.BLUE]) + ' ' + str(detectedBricks[colors.YELLOW]) + '] \t \t ##########################'
                bestOrder[orderProcess]['orderState'] = "GET_ORDER"
                
                rospy.sleep(1.0)
            else:
                print "Waiting for Vision input"
                listReceived=True       # Simulating Vision input
                rospy.sleep(3.0)
                
################################################################################################### 
#--------------------------------------- Get order state ------------------------------------------ 
###################################################################################################                
        if(bestOrder[orderProcess]['orderState'] =="GET_ORDER"):
            bestOrder[orderProcess] = getOrders(requestedOrders, detectedBricks,orderProcess)   
            
            printOrderSpecs(bestOrder[orderProcess])
            
            assignSlider(bestOrder[orderProcess],sliderStatus)
            
            
            publish(bestOrder[orderProcess])
            rospy.sleep(1.0)
            
            
################################################################################################### 
#--------------------------------------- Order done state ----------------------------------------- 
###################################################################################################              
        if(bestOrder[orderProcess]['orderState'] =="ORDER_DONE" and BricksDetected()):
            #deleteOrder(bestOrder[slider]['orderName'],bestOrder[slider]['ticket'] )
            resetSlider(bestOrder[orderProcess],sliderStatus)
            logMsg('COMPLETED', bestOrder[orderProcess]['orderName'])
            # Signal Vision system that the order is done. Wait for new detectedBricks
            bestOrder[orderProcess]['orderState'] = "IDLE"
            
            rospy.sleep(1.0)
            
################################################################################################### 
#--------------------------------------- Order not done state ------------------------------------- 
###################################################################################################        
        if(bestOrder[orderProcess]['orderState'] == "ORDER_NOT_DONE" and sliderStatus[orderProcess]['busy'] == True):        
            detectedBricks = [random.randrange(0, 2),random.randrange(0, 2),random.randrange(0, 2)]
            print '\n ################################ \t New detected bricks [RED BLUE YELLOW]: [ ' + str(detectedBricks[0]), str(detectedBricks[1]), str(detectedBricks[2]) + '] \t \t ##########################'
            
            bestOrder[orderProcess] = getSpecificOrder(bestOrder[orderProcess],detectedBricks,orderProcess)
            
            if(bestOrder[orderProcess]['orderState'] == "ORDER_DONE"):
                resetSlider(bestOrder[orderProcess],sliderStatus)
                
            printOrderSpecs(bestOrder[orderProcess])          
                
            publish(bestOrder[orderProcess])
                
            rospy.sleep(1.0)
        
        
        print "Failed state: " + str(bestOrder[orderProcess]['orderState'])    
        print '\n ################################ \t Slider 0 \t \t ##########################'
        printSliderStatus(sliderStatus[0])
        print '\n ################################ \t Slider 1 \t \t ##########################'
        printSliderStatus(sliderStatus[1])
        
        rospy.sleep(1.0)

################################################################################################### 
#--------------------------------------- ROS topic I/O -------------------------------------------- 
###################################################################################################

if __name__ == '__main__':
   pub = rospy.Publisher('chosenOrder', order)
   rospy.Subscriber("visDetected", order, visCallback)
   main()
