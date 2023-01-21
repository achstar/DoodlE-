import cv2 as cv
import time
import os
from cvzone.HandTrackingModule import HandDetector
from matplotlib.pyplot import draw
from HandTrackerModule import *
import serial

serialcomm = serial.Serial('COM19', 9600)
serialcomm.timeout = 1

cap = cv2.VideoCapture(0)
detector = HandDetector(detectionCon=0.8, maxHands=4) # maybe change maxHands to 2
#previousTime
count = 0
x1 = 0
y1 = 0
pTime = 0
cmd = 'forward'

b = False
time_passed = 0
timerDelay = 100
count = 0

def getCMD(tip, joint, xDiff, yDiff):
    #forward and backward
    if (tip < joint):
        if(xDiff <= -70):
            return 'right'
        elif(xDiff >= 70):
            return 'left'
        return 'forward'
    elif tip > joint:
        if(xDiff <= -70):
            return 'right'
        elif(xDiff >= 70):
            return 'left'
        return 'backward'
    else:
        return 'invalid'


while True:

    success, img = cap.read()
    hands, img = detector.findHands(img)
    
    cTime = time.time()
    pTime = cTime

    tipIds = [4, 8, 12, 16, 20]
    jointIds = [3, 7, 11, 15, 19]

    if hands:
        # Hand 1
        hand1 = hands[0]
        lmList1 = hand1["lmList"]  # List of 21 Landmarks points
        bbox1 = hand1["bbox"]  # Bounding Box info x,y,w,h
        centerPoint1 = hand1["center"]  # center of the hand cx,cy
        handType1 = hand1["type"]  # Hand Type Left or Right

        fingers1 = detector.fingersUp(hand1)
 
        if len(hands) == 2:
            lmList_hand1 = detector.findPosition(img, 1, draw = False)

            hand2 = hands[1]
            lmList2 = hand2["lmList"]  # List of 21 Landmarks points
            bbox2 = hand2["bbox"]  # Bounding Box info x,y,w,h
            centerPoint2 = hand2["center"]  # center of the hand cx,cy
            handType2 = hand2["type"]  # Hand Type Left or Right

            #Finger Counting code
            if len(lmList_hand1) != 0:
                fingers = []
 
            fingers2 = detector.fingersUp(hand2)
            length, info, img = detector.findDistance(centerPoint1, centerPoint2, img)  # with draw

            #centerpoint 1 and centerpoint 2 contain the (x,y) coordinates for each center
            x1,y1 = centerPoint1
            x2,y2 = centerPoint2

        else:
            lmList_hand1 = detector.findPosition(img, 0, draw = False)
            #Finger Counting code
            if len(lmList_hand1) != 0:
                fingers = []

                #Thumb
                #1 x coordinates
                #2 y coordinates 
                if lmList_hand1[tipIds[0]][1] > lmList_hand1[tipIds[0]-1][1]:
                    fingers.append(1)
                else:
                    fingers.append(0)
                
                for id in range(1,5):
                    if lmList_hand1[tipIds[id]][2] < lmList_hand1[tipIds[id]-2][2]:
                        fingers.append(1)
                    else:
                        fingers.append(0)
                    count += 1
                
                #stop
                if fingers.count(1) == 5:
                    cmd = "stop"
                    # print(cmd)
                    # print('stop')
                
                #not a stop, doing other commands
                else:
                    #forward and backward
                    # if lmList_hand1[tipIds[1]][2] < lmList_hand1[tipIds[1]-2][2]:
                    #     #if the tip of the finger is above the joint
                    #     cmd = 'forward'
                    #     # print("forward")
                    # elif lmList_hand1[tipIds[1]][2] > lmList_hand1[tipIds[1]-3][2]:
                    #     cmd = 'backward'
                    #     # print("bacckward")
                    cmdTmp = getCMD(lmList_hand1[tipIds[1]][2], lmList_hand1[tipIds[1]-3][2], lmList_hand1[tipIds[1]][1] - lmList_hand1[tipIds[1]-3][1], lmList_hand1[tipIds[1]][2] - lmList_hand1[tipIds[1]-3][2]);
                    if(cmdTmp != 'invalid'):
                        cmd = cmdTmp
                    # print(cmd)

            x1 = lmList_hand1[tipIds[1]][1]
            y1 = lmList_hand1[tipIds[1]][2]
        

            print(f'One Hand: {fingers}')
    if(count % 10 == 0):
        # print(cmd)
        i = cmd.strip()
        serialcomm.write(i.encode())
        time.sleep(0.5)
        if("invalid input" in serialcomm.readline().decode('ascii')):
            print(serialcomm.readline().decode('ascii'))
            print(cmd)
    cv2.imshow("Image", img)
    cv2.waitKey(1)

    if cv2.waitKey(30) == ord('q'):
        break

serialcomm.close()
cap.release()
if cv2.waitKey(1) == ord('q'):
    cv2.destroyAllWindows()