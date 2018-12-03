//本系统从12引脚接收二进制数据，从13引脚输出二进制数据，接收到的数据通过一个发光二极管（连11引脚）和一个光电二极管（连A0引脚）进行传输
#define ADpin A0
#define led 11
#define in 12
#define out 13
#define T 1000

int numdata;
//bool start=false;


void setup() {
   pinMode(led,OUTPUT);
   pinMode(in,INPUT);
   pinMode(out, OUTPUT);
}

void loop() {
    //读取数据
    
    numdata = digitalRead(in);
   
    //判断传输是否开始
    //if(numdata==1){
    //  start=true;
    //}
   //if(start)
   //{
    //传输数据
    if(numdata==HIGH){
      digitalWrite(led,HIGH);
    }
    if(numdata==LOW){
      digitalWrite(led,LOW);
    }
    
    //数据处理
    if(analogRead(ADpin)>20){
       digitalWrite(out, HIGH);          
    }
    else if(analogRead(ADpin)<20){
       digitalWrite(out, LOW);  
    }    
   //} 
   //delay(T);
}
