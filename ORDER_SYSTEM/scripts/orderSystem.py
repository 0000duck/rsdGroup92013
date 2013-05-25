#!/usr/bin/env python
#import socket   #for sockets
import roslib; roslib.load_manifest('ORDER_SYSTEM')
import rospy
from MESSAGES.msg import order
from std_msgs.msg import Bool
from std_msgs.msg import Int32

import sys                              #for exit
import xml.etree.ElementTree as xml     # XML parsing
import requests                         # REST/HTML requests
from time import gmtime, strftime       # Get current time
import shutil                           # file I/O
from lxml import etree
import random
import warnings
from sphinx.ext import todo

 
################################################################################################### 
#--------------------------------------- Variables ------------------------------------------------ 
################################################################################################### 
IP = '192.168.10.100'
port = 80
detectedBricks = [2,2,2]        # Red, Blue, Yellow (bricks)
ROSDetectedBricks = []
orderTimeOut = []
DetectionsCounter = -1
tempCounter = -1
totalOrdersDone = 0
base_url = 'http://192.168.10.100/'
bestOrder_dict = {0: {'orderName':'None','timeStamp':0,'orderState':"IDLE",'orderDone':True,'slider':-1, 'bricks':0,'ticket':0,'redTotal':0,'blueTotal':0,'yellowTotal':0,'redPicked':0,'bluePicked':0,'yellowPicked':0,'redNeeded':0,'blueNeeded':0,'yellowNeeded':0},        1: {'orderName':'None','timeStamp':0,'orderState':"IDLE",'orderDone':True,'slider':-1, 'bricks':0,'ticket':0,'redTotal':0,'blueTotal':0,'yellowTotal':0,'redPicked':0,'bluePicked':0,'yellowPicked':0,'redNeeded':0,'blueNeeded':0,'yellowNeeded':0}}
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
    
    
def resetSlider(sliderStatus):
    sliderStatus[orderProcess]['busy'] = False
    sliderStatus[orderProcess]['orderName'] = 'None'
    return sliderStatus   
    
def assignSlider(bestOrder,sliderStatus):
    if(sliderStatus[0]['busy'] == False):
        sliderStatus[0]['busy'] = True
        sliderStatus[0]['orderName'] = bestOrder['orderName']
        bestOrder['slider'] = 0
        return sliderStatus
    if(sliderStatus[1]['busy'] == False):
        sliderStatus[1]['busy'] = True
        sliderStatus[1]['orderName'] = bestOrder['orderName']
        bestOrder['slider'] = 1
        return sliderStatus
        
 
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
    try:
        orderList = requests.get(base_url + serverPath(numberOfOrders))
    except Exception, e:
        print "Exception: " + str(e)
        rospy.warning("You're probably on eduroam, you fool!")
        sys.exit()
    if(orderList.status_code != 200):
        rospy.warning('HTTP error')
        
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
            
            bestOrder_dict['orderName'] = orderNames[x]
            
            bestOrder_dict['redPicked'] = bestOrder_dict['redTotal']
            bestOrder_dict['bluePicked'] = bestOrder_dict['blueTotal']
            bestOrder_dict['yellowPicked'] = bestOrder_dict['yellowTotal']
            
            bestOrder_dict['redNeeded'] = bestOrder_dict['redTotal']-bestOrder_dict['redPicked']
            bestOrder_dict['blueNeeded'] = bestOrder_dict['blueTotal']-bestOrder_dict['bluePicked']
            bestOrder_dict['yellowNeeded'] = bestOrder_dict['yellowTotal']-bestOrder_dict['yellowPicked']
            
            orderReceipt = requests.put(base_url + serverPath(orderNames[x]))
            bestOrder_dict['timeStamp'] = rospy.get_time();
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
            if(bestCounter > bestOrder_dict['bricks']):
                
                bestOrder_dict['redTotal'] = bricks[colors.RED]
                bestOrder_dict['blueTotal'] = bricks[colors.BLUE]
                bestOrder_dict['yellowTotal'] = bricks[colors.YELLOW]
                
                bestOrder_dict['bricks'] = bestCounter
                
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
    bestOrder_dict['timeStamp'] = rospy.get_time();
    bestOrder_dict['ticket'] = parseOrderReceipt(orderReceipt.content)
    bestOrder_dict['orderState'] = "ORDER_NOT_DONE"
    
    print '\n ################################ \t An order was found: ' + str(bestOrder_dict['orderName']) + ' with ticket: ' + str(bestOrder_dict['ticket']) + '\t ##########################'
    return bestOrder_dict


def getSpecificOrder(prevOrderDetails,detectedBricks,orderProcess):
    print '\n ################################ \t Continued processing order: ' + prevOrderDetails['orderName'] + '\t ##########################'
    bricks = [0,0,0]
    bricks[colors.RED] = prevOrderDetails['redNeeded']      # We subtract the bricks that have already been picked up in the previous batch
    if bricks[colors.RED] < 0:                      # Clamping
        bricks[colors.RED] = 0
    bricks[colors.BLUE] = prevOrderDetails['blueNeeded']
    if bricks[colors.BLUE] < 0:
        bricks[colors.BLUE] = 0
    bricks[colors.YELLOW] = prevOrderDetails['yellowNeeded']
    if bricks[colors.YELLOW] < 0:
        bricks[colors.YELLOW] = 0
        
    if((bricks[colors.RED] <= detectedBricks[colors.RED]) & (bricks[colors.BLUE] <= detectedBricks[colors.BLUE]) & (bricks[colors.YELLOW] <= detectedBricks[colors.YELLOW])):    # Every need can be fulfilled
        bestOrder_dict['redPicked'] = prevOrderDetails['redNeeded']
        bestOrder_dict['bluePicked'] = prevOrderDetails['blueNeeded']
        bestOrder_dict['yellowPicked'] = prevOrderDetails['yellowNeeded']
        
        bestOrder_dict['redNeeded'] = 0
        bestOrder_dict['blueNeeded'] = 0
        bestOrder_dict['yellowNeeded'] = 0
        
        bestOrder_dict['orderName'] = prevOrderDetails['orderName']
        print '\n ################################ \t Finished order: ' + str(prevOrderDetails['orderName']) + ' with ticket: ' + str(prevOrderDetails['ticket']) + '\t ##################'
        bestOrder_dict['orderState'] = "ORDER_DONE"
        return bestOrder_dict
    else:
         
        if(bestOrder_dict['redNeeded'] <= detectedBricks[colors.RED] and detectedBricks[colors.RED] != 0):
            bestOrder_dict['redPicked'] = bricks[colors.RED]
        elif(detectedBricks[colors.RED] == 0):
            bestOrder_dict['redPicked'] = 0
            
        if(bestOrder_dict['redNeeded'] > detectedBricks[colors.RED]):
            bestOrder_dict['redPicked'] = detectedBricks[colors.RED]
        
        if(bestOrder_dict['blueNeeded'] <= detectedBricks[colors.BLUE] and detectedBricks[colors.BLUE] != 0):
            bestOrder_dict['bluePicked'] = bricks[colors.BLUE]
        elif(detectedBricks[colors.BLUE] == 0):
            bestOrder_dict['bluePicked'] = 0    
            
        if(bestOrder_dict['blueNeeded'] > detectedBricks[colors.BLUE]):
            bestOrder_dict['bluePicked'] = detectedBricks[colors.BLUE]
             
        if(bestOrder_dict['yellowNeeded'] <= detectedBricks[colors.YELLOW] and detectedBricks[colors.YELLOW] != 0):
            bestOrder_dict['yellowPicked'] = bricks[colors.YELLOW]
        elif(detectedBricks[colors.YELLOW] == 0):
            bestOrder_dict['yellowPicked'] = 0
            
        if(bestOrder_dict['yellowNeeded'] > detectedBricks[colors.YELLOW]):
            bestOrder_dict['yellowPicked'] = detectedBricks[colors.YELLOW]
            

        bestOrder_dict['redNeeded'] -= bestOrder_dict['redPicked']            
  
        bestOrder_dict['blueNeeded'] -= bestOrder_dict['bluePicked']
           
        bestOrder_dict['yellowNeeded'] -= bestOrder_dict['yellowPicked']
    
        if(bestOrder_dict['redNeeded'] <= 0 and bestOrder_dict['blueNeeded'] <= 0 and bestOrder_dict['yellowNeeded'] <= 0):
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
                
                
def removeOldOrders(bestorder):
    bestOrder[orderProcess].clear();
    bestOrder[orderProcess]['orderState'] = 'IDLE'
    bestOrder[orderProcess]['orderName'] = 'None'
    bestOrder[orderProcess]['orderDone'] = True
    bestOrder[orderProcess]['redNeeded'] = 0
    bestOrder[orderProcess]['blueNeeded'] = 0
    bestOrder[orderProcess]['yellowNeeded'] = 0
    bestOrder[orderProcess]['timeStamp'] = 0
    return bestOrder
    
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
    else:
        print 'Error sending log!'
    return log




################################################################################################### 
#--------------------------------------- ROS functions -------------------------------------------- 
################################################################################################### 


def publish(bestOrder):
    # Telling the robot what bricks to pick up
    pub_msg = order()
    pub_msg.header.stamp = rospy.get_rostime()
    pub_msg.red = bestOrder['redPicked']
    pub_msg.blue = bestOrder['bluePicked']
    pub_msg.yellow = bestOrder['yellowPicked']
    pub_msg.slider = bestOrder['slider']
    global pub
    pub.publish(pub_msg)
 

def publishOrderBegun():
    pubBegunMsg = Bool()
    pubBegunMsg.data = True
    global pubOrderBegun
    pubOrderBegun.publish(pubBegunMsg)
    
    
def publishTotalOrders(totalOrdersDone):
    pubTotalMsg = Int32()
    pubTotalMsg.data = totalOrdersDone
    global pubTotalOrders
    pubTotalOrders.publish(pubTotalMsg)
    


################################################################################################### 
#--------------------------------------- Main program --------------------------------------------- 
################################################################################################### 

def visCallback(data):
    global DetectionsCounter
    if(data.red == 0 and data.blue == 0 and data.yellow == 0):
        print 'No bricks detected'
    else:
        DetectionsCounter = DetectionsCounter + 1
        #listReceived = True
        print 'Input data: ' + str(data.red) + ', ' + str(data.blue) + ', ' + str(data.yellow)
        tempBricks = [data.red,data.blue,data.yellow]
        ROSDetectedBricks.append(tempBricks) 
        print "ROS array: " + str(ROSDetectedBricks)
    

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
    global DetectionsCounter
    global detectedBricks
    global ROSDetectedBricks
    global tempCounter
    sliderStatus = dict(slider_dict)
    bestOrder = dict(bestOrder_dict)
    ongoingOrder = dict(bestOrder_dict)
    while not rospy.is_shutdown():
        try:
            #while (detectedBricks[colors.RED]== 0 and detectedBricks[colors.BLUE]== 0 and detectedBricks[colors.YELLOW]== 0):
            while(DetectionsCounter < 0 and not rospy.is_shutdown()):
                print  '\n ################################ \t Waiting for detected bricks \t \t ##########################'
                elapsed = rospy.get_time() - bestOrder[orderProcess]['timeStamp']
                #print "timeStamp order: " + str(bestOrder[orderProcess]['orderName']) + " " + str(bestOrder[orderProcess]['timeStamp'])
                
                if(int(elapsed) > 40):   # CHANGE THIS!!!!!!!!!!
                    print 'Order ' + str(bestOrder[orderProcess]['orderName']) + ' has timed out!'
                    bestOrder = removeOldOrders(bestOrder)
                    sliderStatus[orderProcess]['orderName'] = 'None'
                    sliderStatus[orderProcess]['busy'] = False
                orderProcess = not orderProcess
                rospy.sleep(2.0)
        except KeyboardInterrupt:
            sys.exit()
        
        if((bestOrder[orderProcess]['redNeeded'] + bestOrder[orderProcess]['blueNeeded'] + bestOrder[orderProcess]['yellowNeeded']) > (bestOrder[not orderProcess]['redNeeded'] + bestOrder[not orderProcess]['blueNeeded'] + bestOrder[not orderProcess]['yellowNeeded']) ):
            orderProcess = not orderProcess
        tempCounter = DetectionsCounter     # Finding out if there is a detection available

################################################################################################### 
#--------------------------------------- Idle state -----------------------------------------------
###################################################################################################         
        
        if (bestOrder[orderProcess]['orderState'] == "IDLE" and tempCounter >= 0):
            if(tempCounter >= 0):
                
                print '\n ################################ \t Order thread ' + str(int(orderProcess)) + ' processing \t \t \t \t ##########################'
                print '\n ################################ \t Detected bricks [RED BLUE YELLOW]: [' +  str(ROSDetectedBricks[tempCounter][colors.RED]) + ' ' + str(ROSDetectedBricks[tempCounter][colors.BLUE]) + ' ' + str(ROSDetectedBricks[tempCounter][colors.YELLOW]) + '] \t \t ##########################'
                bestOrder[orderProcess]['orderState'] = "GET_ORDER"
                
################################################################################################### 
#--------------------------------------- Get order state ------------------------------------------ 
###################################################################################################                
        if(bestOrder[orderProcess]['orderState'] =="GET_ORDER" and tempCounter >= 0):
            bestOrder[orderProcess] = getOrders(requestedOrders, ROSDetectedBricks[tempCounter],orderProcess)   
            
            logMsg('NEW_ORDER', bestOrder[orderProcess]['orderName'])
            publishOrderBegun()
            
            printOrderSpecs(bestOrder[orderProcess])
            
            sliderStatus = assignSlider(bestOrder[orderProcess],sliderStatus)
            if(sliderStatus[0]['orderName'] == bestOrder[orderProcess]['orderName']):
                bestOrder[orderProcess]['slider'] = 0
            elif(sliderStatus[1]['orderName'] == bestOrder[orderProcess]['orderName']):
                bestOrder[orderProcess]['slider'] = 1
            
            print '\n ################################ \t Publishing new order: ' + str(bestOrder[orderProcess]['orderName']) + ' from order thread ' + str(int(orderProcess)) + '\t \t ##########################'
            publish(bestOrder[orderProcess])
            
            print '\n ################################ \t Slider 0 \t \t ##########################'
            printSliderStatus(sliderStatus[0])
            print '\n ################################ \t Slider 1 \t \t ##########################'
            printSliderStatus(sliderStatus[1])
            
            ROSDetectedBricks.pop(tempCounter)   
            tempCounter = tempCounter - 1                                   # Remove detection list from input array and wait for new detection
            DetectionsCounter = DetectionsCounter - 1
            
            
################################################################################################### 
#--------------------------------------- Order not done state ------------------------------------- 
###################################################################################################        
        if(bestOrder[orderProcess]['orderState'] == "ORDER_NOT_DONE" and tempCounter >= 0):
            #print "timeStamp order: " + bestOrder[orderProcess]['orderName'] + " " + str(rospy.Duration.from_sec(bestOrder[orderProcess]['timeStamp']))
            
            elapsed = rospy.get_time() - bestOrder[orderProcess]['timeStamp']
            if(int(elapsed) > 60):   # CHANGE THIS!!!!!!!!!!
                print 'Order ' + str(bestOrder[orderProcess]['orderName']) + ' has timed out!'
                bestOrder = removeOldOrders(bestOrder)
                sliderStatus[orderProcess]['orderName'] = 'None'
                sliderStatus[orderProcess]['busy'] = False
                
            else:      
                #detectedBricks = [random.randrange(0, 4),random.randrange(0, 4),random.randrange(0, 4)]
                print '\n ################################ \t New detected bricks [RED BLUE YELLOW]: [ ' + str(ROSDetectedBricks[tempCounter][colors.RED]), str(ROSDetectedBricks[tempCounter][colors.BLUE]), str(ROSDetectedBricks[tempCounter][colors.YELLOW]) + '] \t \t ##########################'
                
                bestOrder[orderProcess] = getSpecificOrder(bestOrder[orderProcess],ROSDetectedBricks[tempCounter],orderProcess)
                
                print '\n ################################ \t Publishing old order: ' + str(bestOrder[orderProcess]['orderName']) + ' from order thread ' + str(int(orderProcess)) + '\t \t ##########################'
                publish(bestOrder[orderProcess])
                
                if(bestOrder[orderProcess]['orderState'] == "ORDER_DONE"):
                    sliderStatus = resetSlider(sliderStatus)
                    
                printOrderSpecs(bestOrder[orderProcess])          
                
                print '\n ################################ \t Slider 0 \t \t ##########################'
                printSliderStatus(sliderStatus[0])
                print '\n ################################ \t Slider 1 \t \t ##########################'
                printSliderStatus(sliderStatus[1])    
                
                ROSDetectedBricks.pop(tempCounter)   
                tempCounter = tempCounter - 1                                   # Remove detection list from input array and wait for new detection
                DetectionsCounter = DetectionsCounter - 1    
        
        
################################################################################################### 
#--------------------------------------- Order done state ----------------------------------------- 
###################################################################################################              
        if(bestOrder[orderProcess]['orderState'] =="ORDER_DONE"):
            #deleteOrder(bestOrder[slider]['orderName'],bestOrder[slider]['ticket'] )
            sliderStatus = resetSlider(sliderStatus)
            bestOrder[orderProcess]['slider'] = -1                           # To indicate that no slider is assigned
            logMsg('COMPLETED', bestOrder[orderProcess]['orderName'])
            #totalOrdersDone = totalOrdersDone + 1
            #publishTotalOrders(totalOrdersDone)
            # Signal Vision system that the order is done. Wait for new detectedBricks
            bestOrder[orderProcess]['orderState'] = "IDLE"

################################################################################################### 
#--------------------------------------- ROS topic I/O -------------------------------------------- 
###################################################################################################

if __name__ == '__main__':
   pub = rospy.Publisher('/chosenOrder', order)
   pubTotalOrders = rospy.Publisher('/totalOrders', Int32)
   pubOrderBegun = rospy.Publisher('/orderBegun', Bool)
   rospy.Subscriber("/visDetected", order, visCallback)
   main()
