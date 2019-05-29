// This #include statement was automatically added by the Particle IDE.
#include <MQTT.h>


// This #include statement was automatically added by the Particle IDE.
#include <SparkIntervalTimer.h>


void callback(char* topic, byte* payload, unsigned int length) 
{
    
}
MQTT client("test.mosquitto.org", 1883, callback);
extern void interruptSetup(void);

extern int pulsePin;
extern int blinkPin;
extern volatile int BPM;;
extern volatile int rawSignal;;
extern volatile int IBI;
extern volatile boolean Pulse;
extern volatile boolean QS;


static boolean serialVisual = false;   // Set to 'false' by Default.  Re-set to 'true' to see Arduino Serial Monitor ASCII Visual Pulse 


extern int fadePin;
extern int fadeRate;


void setup()
{
	pinMode(blinkPin,OUTPUT);         // pin that will blink to your heartbeat!
	pinMode(fadePin,OUTPUT);          // pin that will fade to your heartbeat!
	interruptSetup();  
	client.connect("photonDev");// sets up to read Pulse Sensor signal every 2mS 
}



//  Where the Magic Happens
void loop()
{

	//serialOutput() ;       
	if (client.isConnected())
	{
	    if (QS == true){     //  A Heartbeat Was Found
		// BPM and IBI have been Determined
		// Quantified Self "QS" true when arduino finds a heartbeat
		digitalWrite(blinkPin,HIGH);     // Blink LED, we got a beat. 
		fadeRate = 255;      
		Particle.publish("pulse",String(IBI),PRIVATE); // Publish the IBI to thingSpeak
		client.publish("photonLog",String(IBI)); // publish the reading to pi
		QS = false;         // set QS to false
		} 
		else 
		{ 
		    digitalWrite(blinkPin,LOW);
		    delay(20);
		}
		client.loop();
	
	
	 }  
}
