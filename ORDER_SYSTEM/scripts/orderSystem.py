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
orders = []
totalOrdersDone = 0
base_url = 'http://192.168.10.100/'
orders_dict = {'orderName':'None','timeStamp':0,'orderState':"IDLE",'orderDone':True,'slider':-1, 'bricks':0,'ticket':0,'redTotal':0,'blueTotal':0,'yellowTotal':0,'redPicked':0,'bluePicked':0,'yellowPicked':0,'redNeeded':0,'blueNeeded':0,'yellowNeeded':0}
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
    
def assignSlider(orders,sliderStatus):
    if(sliderStatus[0]['busy'] == False):
        sliderStatus[0]['busy'] = True
        sliderStatus[0]['orderName'] = orders['orderName']
        orders['slider'] = 0
        return sliderStatus
    elif(sliderStatus[1]['busy'] == False):
        sliderStatus[1]['busy'] = True
        sliderStatus[1]['orderName'] = orders['orderName']
        orders['slider'] = 1
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
    newOrder = dict(orders_dict)
    newOrder['bricks'] = 0
    for x in range(0,int(numberOfOrders)):
        bestCounter = 0
        orderDetails = requests.get(base_url + serverPath(orderNames[x]))
        bricks[colors.RED] = int(parseorderDetails(orderDetails.content,'red'))
        bricks[colors.BLUE] = int(parseorderDetails(orderDetails.content,'blue'))
        bricks[colors.YELLOW] = int(parseorderDetails(orderDetails.content,'yellow'))
        

        
        print '\n ################################ \t Order ' + orderNames[x] + ' requires [RED BLUE YELLOW]: ' + '[' + str(bricks[colors.RED]) + ' ' + str(bricks[colors.BLUE]) + ' ' + str(bricks[colors.YELLOW]) + '] \t ##########################'
        #print orderDetails.content
        
        if((bricks[colors.RED] <= detectedBricks[colors.RED]) & (bricks[colors.BLUE] <= detectedBricks[colors.BLUE]) & (bricks[colors.YELLOW] <= detectedBricks[colors.YELLOW])):    # Every need can be fulfilled
            
            newOrder['redTotal'] = bricks[colors.RED]
            newOrder['blueTotal'] = bricks[colors.BLUE]
            newOrder['yellowTotal'] = bricks[colors.YELLOW]
            
            newOrder['orderName'] = orderNames[x]
            
            newOrder['redPicked'] = newOrder['redTotal']
            newOrder['bluePicked'] = newOrder['blueTotal']
            newOrder['yellowPicked'] = newOrder['yellowTotal']
            
            newOrder['redNeeded'] = newOrder['redTotal']-newOrder['redPicked']
            newOrder['blueNeeded'] = newOrder['blueTotal']-newOrder['bluePicked']
            newOrder['yellowNeeded'] = newOrder['yellowTotal']-newOrder['yellowPicked']
            
            orderReceipt = requests.put(base_url + serverPath(orderNames[x]))
            newOrder['timeStamp'] = rospy.get_time();
            newOrder['ticket'] = parseOrderReceipt(orderReceipt.content)
            print '\n ################################ \t An optimal order was found: ' + orderNames[x] + ' with ticket: ' + newOrder['ticket'] + '\t ##################'
            newOrder['orderState'] = "ORDER_DONE"
            return newOrder
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
            if(bestCounter > newOrder['bricks']):
                
                newOrder['redTotal'] = bricks[colors.RED]
                newOrder['blueTotal'] = bricks[colors.BLUE]
                newOrder['yellowTotal'] = bricks[colors.YELLOW]
                
                newOrder['bricks'] = bestCounter
                
                newOrder['orderName'] = orderNames[x]
                
                
                if(newOrder['redTotal'] <= detectedBricks[colors.RED]):
                    newOrder['redPicked'] = bricks[colors.RED]
                if(newOrder['redTotal'] > detectedBricks[colors.RED]):
                    newOrder['redPicked'] = detectedBricks[colors.RED]
                    
                if(newOrder['blueTotal'] <= detectedBricks[colors.BLUE]):
                    newOrder['bluePicked'] = bricks[colors.BLUE]
                if(newOrder['blueTotal'] > detectedBricks[colors.BLUE]):
                    newOrder['bluePicked'] = detectedBricks[colors.BLUE]
                    
                if(newOrder['yellowTotal'] <= detectedBricks[colors.YELLOW]):
                    newOrder['yellowPicked'] = bricks[colors.YELLOW]
                if(newOrder['yellowTotal'] > detectedBricks[colors.YELLOW]):
                    newOrder['yellowPicked'] = detectedBricks[colors.YELLOW]
                  
                newOrder['redNeeded'] = newOrder['redTotal']-newOrder['redPicked']    
                newOrder['blueNeeded'] = newOrder['blueTotal']-newOrder['bluePicked']
                newOrder['yellowNeeded'] = newOrder['yellowTotal']-newOrder['yellowPicked']    
    
    orderReceipt = requests.put(base_url + serverPath(newOrder['orderName']))
    newOrder['timeStamp'] = rospy.get_time();
    newOrder['ticket'] = parseOrderReceipt(orderReceipt.content)
    newOrder['orderState'] = "ORDER_NOT_DONE"
    
    print '\n ################################ \t An order was found: ' + str(newOrder['orderName']) + ' with ticket: ' + str(newOrder['ticket']) + '\t ##########################'
    return newOrder


def getSpecificOrder(prevOrderDetails,detectedBricks):
    
    newOrder = dict(orders_dict)
    
    newOrder['redNeeded'] = prevOrderDetails['redNeeded']
    newOrder['blueNeeded'] = prevOrderDetails['blueNeeded']
    newOrder['yellowNeeded'] = prevOrderDetails['yellowNeeded']
    newOrder['redTotal'] = prevOrderDetails['redTotal']
    newOrder['blueTotal'] = prevOrderDetails['blueTotal']
    newOrder['yellowTotal'] = prevOrderDetails['yellowTotal']
    newOrder['orderName'] = prevOrderDetails['orderName']
    newOrder['ticket'] = prevOrderDetails['ticket']
    newOrder['slider'] = prevOrderDetails['slider']
    newOrder['timeStamp'] = prevOrderDetails['timeStamp']
    
    
    #print "Prev1 red: " + str(prevOrderDetails['redNeeded']) + " prev1 blue: " + str(prevOrderDetails['blueNeeded']) + " prev1 yellow: " + str(prevOrderDetails['yellowNeeded'])
    print '\n ################################ \t Continued processing order: ' + prevOrderDetails['orderName'] + '\t ##########################'
    bricks = [0,0,0]
    bricks[colors.RED] = prevOrderDetails['redNeeded']      # We subtract the bricks that have already picked up in the previous batch
    if bricks[colors.RED] < 0:                      # Clamping
        bricks[colors.RED] = 0
    bricks[colors.BLUE] = prevOrderDetails['blueNeeded']
    if bricks[colors.BLUE] < 0:
        bricks[colors.BLUE] = 0
    bricks[colors.YELLOW] = prevOrderDetails['yellowNeeded']
    if bricks[colors.YELLOW] < 0:
        bricks[colors.YELLOW] = 0
    
    if((bricks[colors.RED] <= detectedBricks[colors.RED]) & (bricks[colors.BLUE] <= detectedBricks[colors.BLUE]) & (bricks[colors.YELLOW] <= detectedBricks[colors.YELLOW])):    # Every need can be fulfilled
        newOrder['redPicked'] = prevOrderDetails['redNeeded']
        newOrder['bluePicked'] = prevOrderDetails['blueNeeded']
        newOrder['yellowPicked'] = prevOrderDetails['yellowNeeded']
        
        newOrder['redNeeded'] = 0
        newOrder['blueNeeded'] = 0
        newOrder['yellowNeeded'] = 0
        
        print '\n ################################ \t Finished order: ' + str(prevOrderDetails['orderName']) + ' with ticket: ' + str(prevOrderDetails['ticket']) + '\t ##################'
        newOrder['orderState'] = "ORDER_DONE"
        return newOrder
    else:
         
        if(newOrder['redNeeded'] <= detectedBricks[colors.RED] and detectedBricks[colors.RED] != 0):
            newOrder['redPicked'] = bricks[colors.RED]
        elif(detectedBricks[colors.RED] == 0):
            newOrder['redPicked'] = 0
            
        if(newOrder['redNeeded'] > detectedBricks[colors.RED]):
            newOrder['redPicked'] = detectedBricks[colors.RED]
        
        if(newOrder['blueNeeded'] <= detectedBricks[colors.BLUE] and detectedBricks[colors.BLUE] != 0):
            newOrder['bluePicked'] = bricks[colors.BLUE]
        elif(detectedBricks[colors.BLUE] == 0):
            newOrder['bluePicked'] = 0    
            
        if(newOrder['blueNeeded'] > detectedBricks[colors.BLUE]):
            newOrder['bluePicked'] = detectedBricks[colors.BLUE]
             
        if(newOrder['yellowNeeded'] <= detectedBricks[colors.YELLOW] and detectedBricks[colors.YELLOW] != 0):
            newOrder['yellowPicked'] = bricks[colors.YELLOW]
        elif(detectedBricks[colors.YELLOW] == 0):
            newOrder['yellowPicked'] = 0
            
        if(newOrder['yellowNeeded'] > detectedBricks[colors.YELLOW]):
            newOrder['yellowPicked'] = detectedBricks[colors.YELLOW]
            
        #print "Prev2 red: " + str(newOrder['redNeeded']) + " prev2 blue: " + str(newOrder['blueNeeded']) + " prev2 yellow: " + str(newOrder['yellowNeeded'])
        newOrder['redNeeded'] -= newOrder['redPicked']            
  
        newOrder['blueNeeded'] -= newOrder['bluePicked']
           
        newOrder['yellowNeeded'] -= newOrder['yellowPicked']
    
        #print "Prev3 red: " + str(newOrder['redNeeded']) + " prev3 blue: " + str(newOrder['blueNeeded']) + " prev3 yellow: " + str(newOrder['yellowNeeded'])
        if(newOrder['redNeeded'] <= 0 and newOrder['blueNeeded'] <= 0 and newOrder['yellowNeeded'] <= 0):
            newOrder['orderState'] = "ORDER_DONE"
        else:
            newOrder['orderState'] = "ORDER_NOT_DONE"
        
    
    return newOrder
    
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
                
                
def removeOldOrders(orders):
    orders[orderProcess].clear();
    orders[orderProcess]['orderState'] = 'IDLE'
    orders[orderProcess]['orderName'] = 'None'
    orders[orderProcess]['orderDone'] = True
    orders[orderProcess]['redNeeded'] = 0
    orders[orderProcess]['blueNeeded'] = 0
    orders[orderProcess]['yellowNeeded'] = 0
    orders[orderProcess]['timeStamp'] = 0
    return orders
    
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


def publish(orders):
    # Telling the robot what bricks to pick up
    pub_msg = order()
    pub_msg.header.stamp = rospy.get_rostime()
    pub_msg.red = orders['redPicked']
    pub_msg.blue = orders['bluePicked']
    pub_msg.yellow = orders['yellowPicked']
    pub_msg.slider = orders['slider']
    global pub
    pub.publish(pub_msg)
 
 
def publishNeededBricks(orders):
    # Telling the GUI what the order still needs
    pub_msg = order()
    pub_msg.header.stamp = rospy.get_rostime()
    print 'red N: ' + str(orders['redNeeded'])
    pub_msg.red = orders['redNeeded']
    pub_msg.blue = orders['blueNeeded']
    pub_msg.yellow = orders['yellowNeeded']
    pub_msg.slider = orders['slider']
    global pubGUI
    pubGUI.publish(pub_msg)

def publishOrderBegun():
    pubBegunMsg = Bool()
    if(orderProcess == True):
        pubBegunMsg.data = 1
    else:
        pubBegunMsg.data = 0
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
        tempBricks = [data.red,data.blue,data.yellow]
        ROSDetectedBricks.append(tempBricks)
    

################################################################################################### 
#--------------------------------------- Main function -------------------------------------------- 
###################################################################################################     

def main():
    rospy.init_node('orderSystem')
    
    listReceived = True
    requestedOrders = '5'
    global orders
    global ongoingOrder
    global orderProcess
    global sliderStatus
    global DetectionsCounter
    global detectedBricks
    global ROSDetectedBricks
    global tempCounter
    global totalOrdersDone
    sliderStatus = dict(slider_dict)
    bestOrder = dict(orders_dict)
    orders.append(bestOrder)        # Initialize the two orders
    orders.append(bestOrder)
    ongoingOrder = dict(orders_dict)
    while not rospy.is_shutdown():
        try:
            while(DetectionsCounter < 0 and not rospy.is_shutdown()):
                print  '\n ################################ \t Waiting for detected bricks \t \t ##########################'
                elapsed = rospy.get_time() - orders[orderProcess]['timeStamp']
                if(int(elapsed) > 180):   # CHANGE THIS!!!!!!!!!!
                    if(orders[orderProcess]['orderName'] != 'None'):
                        print 'Order ' + str(orders[orderProcess]['orderName']) + ' has timed out!'
                    orders = removeOldOrders(orders)
                    sliderStatus[orderProcess]['orderName'] = 'None'
                    sliderStatus[orderProcess]['busy'] = False
                orderProcess = not orderProcess
                rospy.sleep(2.0)
        except KeyboardInterrupt:
            sys.exit()
        if((orders[orderProcess]['redNeeded'] + orders[orderProcess]['blueNeeded'] + orders[orderProcess]['yellowNeeded']) > (orders[not orderProcess]['redNeeded'] + orders[not orderProcess]['blueNeeded'] + orders[not orderProcess]['yellowNeeded']) ):
            orderProcess = not orderProcess
        tempCounter = DetectionsCounter     # Finding out if there is a detection available

################################################################################################### 
#--------------------------------------- Idle state -----------------------------------------------
###################################################################################################         
        if (orders[orderProcess]['orderState'] == "IDLE" and tempCounter >= 0):
            if(tempCounter >= 0):
                
                print '\n ################################ \t Order thread ' + str(int(orderProcess)) + ' processing \t \t \t \t ##########################'
                print '\n ################################ \t Detected bricks [RED BLUE YELLOW]: [' +  str(ROSDetectedBricks[tempCounter][colors.RED]) + ' ' + str(ROSDetectedBricks[tempCounter][colors.BLUE]) + ' ' + str(ROSDetectedBricks[tempCounter][colors.YELLOW]) + '] \t \t ##########################'
                orders[orderProcess]['orderState'] = "GET_ORDER"
                
################################################################################################### 
#--------------------------------------- Get order state ------------------------------------------ 
###################################################################################################                
        if(orders[orderProcess]['orderState'] =="GET_ORDER" and tempCounter >= 0):
            
            #print "orderProc(getORDER): " + str(orderProcess)
            #print "orderP0: " + str(orders[orderProcess]) + "\n\n"
            #print "orderP0: " + str(orders[not orderProcess]) + "\n\n"
            orders[orderProcess] = getOrders(requestedOrders, ROSDetectedBricks[tempCounter],orderProcess)   
            #print "orderP3: " + str(orders[orderProcess]) + "\n\n"
            #print "orderP3: " + str(orders[not orderProcess]) + "\n\n"
        
            
            logMsg('ORDER_START', orders[orderProcess]['orderName'])
            publishOrderBegun()
            
            printOrderSpecs(orders[orderProcess])
            
            #print '\n ################################ \t Before Slider 0 \t \t ##########################'
            #printSliderStatus(sliderStatus[0])
            #print '\n ################################ \t Before Slider 1 \t \t ##########################'
            #printSliderStatus(sliderStatus[1])   
            
            
            sliderStatus = assignSlider(orders[orderProcess],sliderStatus)
            if(sliderStatus[0]['orderName'] == orders[orderProcess]['orderName']):
                orders[orderProcess]['slider'] = 0
            elif(sliderStatus[1]['orderName'] == orders[orderProcess]['orderName']):
                orders[orderProcess]['slider'] = 1
            
            print '\n ################################ \t Publishing new order: ' + str(orders[orderProcess]['orderName']) + ' from order thread ' + str(int(orderProcess)) + '\t \t ##########################'
            publish(orders[orderProcess])
            
            print '\n ################################ \t Slider 0 \t \t ##########################'
            printSliderStatus(sliderStatus[0])
            print '\n ################################ \t Slider 1 \t \t ##########################'
            printSliderStatus(sliderStatus[1])
            
            publishNeededBricks(orders[orderProcess])
            
            ROSDetectedBricks.pop(tempCounter)   
            tempCounter = tempCounter - 1                                   # Remove detection list from input array and wait for new detection
            DetectionsCounter = DetectionsCounter - 1
            
            
################################################################################################### 
#--------------------------------------- Order not done state ------------------------------------- 
###################################################################################################        
        if(orders[orderProcess]['orderState'] == "ORDER_NOT_DONE" and tempCounter >= 0):
            
            elapsed = rospy.get_time() - orders[orderProcess]['timeStamp']
            if(int(elapsed) > 180):   # CHANGE THIS!!!!!!!!!!
                print 'Order ' + str(orders[orderProcess]['orderName']) + ' has timed out!'
                orders = removeOldOrders(orders)
                sliderStatus[orderProcess]['orderName'] = 'None'
                sliderStatus[orderProcess]['busy'] = False
                
            #else:      # REMEMBER INDENTATION HERE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            print '\n ################################ \t New detected bricks [RED BLUE YELLOW]: [ ' + str(ROSDetectedBricks[tempCounter][colors.RED]), str(ROSDetectedBricks[tempCounter][colors.BLUE]), str(ROSDetectedBricks[tempCounter][colors.YELLOW]) + '] \t \t ##########################'
            
            
            #print "orderP5: " + str(orders[orderProcess]) + "\n\n"
            #print "orderP5: " + str(orders[not orderProcess]) + "\n\n"
            orders[orderProcess] = getSpecificOrder(orders[orderProcess],ROSDetectedBricks[tempCounter])
            #print "orderP6: " + str(orders[orderProcess]) + "\n\n"
            #print "orderP6: " + str(orders[not orderProcess]) + "\n\n"
            
            
            print '\n ################################ \t Publishing old order: ' + str(orders[orderProcess]['orderName']) + ' from order thread ' + str(int(orderProcess)) + '\t \t ##########################'
            publish(orders[orderProcess])
            
            if(orders[orderProcess]['orderState'] == "ORDER_DONE"):
                sliderStatus = resetSlider(sliderStatus)
                
            printOrderSpecs(orders[orderProcess])          
            
            print '\n ################################ \t Slider 0 \t \t ##########################'
            printSliderStatus(sliderStatus[0])
            print '\n ################################ \t Slider 1 \t \t ##########################'
            printSliderStatus(sliderStatus[1])    
            
            publishNeededBricks(orders[orderProcess])
            
            ROSDetectedBricks.pop(tempCounter)   
            tempCounter = tempCounter - 1                                   # Remove detection list from input array and wait for new detection
            DetectionsCounter = DetectionsCounter - 1    
        
        
################################################################################################### 
#--------------------------------------- Order done state ----------------------------------------- 
###################################################################################################              
        if(orders[orderProcess]['orderState'] =="ORDER_DONE"):
            deleteOrder(orders[slider]['orderName'],orders[slider]['ticket'] )
            sliderStatus = resetSlider(sliderStatus)
            orders[orderProcess]['slider'] = -1                           # To indicate that no slider is assigned
            logMsg('ORDER_DONE', orders[orderProcess]['orderName'])
            totalOrdersDone = totalOrdersDone + 1
            publishTotalOrders(totalOrdersDone)
            publishNeededBricks(orders[orderProcess])
            # Signal Vision system that the order is done. Wait for new detectedBricks
            orders[orderProcess]['orderState'] = "IDLE"

################################################################################################### 
#--------------------------------------- ROS topic I/O -------------------------------------------- 
###################################################################################################

if __name__ == '__main__':
   pub = rospy.Publisher('/chosenOrder', order)
   pubGUI = rospy.Publisher('/bricksNeeded',order)
   pubTotalOrders = rospy.Publisher('/totalOrders', Int32)
   pubOrderBegun = rospy.Publisher('/orderBegun', Bool)
   rospy.Subscriber("/visDetected", order, visCallback)
   main()
