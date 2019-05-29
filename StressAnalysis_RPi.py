import paho.mqtt.client as mqtt
#import paho.mqtt.publish as publish
import time 


def messageFunction(client,userdata,message):
    IBI = []
    

    topic = str(message.topic)
    message = str(message.payload.decode("utf-8"))
    #print("BPM :" + message)
    ibi = int(message)
    stcount = 0
    
    if(ibi > 640):  # IBI shoud be less than 640 this is set only to demonstrate
        IBI.append(ibi)
        #Timestart = time.clock()
        #stcount += 1
        print("Stress Warning: ",ibi)
    
    
    

ourClient = mqtt.Client("stress_mqtt")
ourClient.connect("test.mosquitto.org",1883)
ourClient.subscribe("photonLog")
ourClient.on_message = messageFunction

ourClient.loop_forever()

