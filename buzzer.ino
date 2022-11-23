unsigned long timed,time0,time;  //时间控制变量
int key=0;                       //选择控制变量
int first;                       //第一个按钮号
float power=1;                   //pwm功率
float pch=1;                  //呼吸灯变速
int highpower=70;               //max pwm power
int skey1=0,skey2=0,skey3=0,skey4=0,skey5=0,skey6=0;                      //权限刷新
int mpower=110;

int pl1o=10;
int pl2o=11;
int pl3o=3;
int pl4o=5; 
int pl5o=6;
int pl6o=9;

int pl1i=4;
int pl2i=7;
int pl3i=8;
int pl4i=12;
int pl5i=1;
int pl6i=13;


int go1,go2,go3,go4,go5,go6;//参与权限

//参与权限变量：
int st1=0,st2=0,st3=0,st4=0,st5=0,st6=0;

void setup(){
pinMode(pl1o,OUTPUT);
pinMode(pl2o,OUTPUT);
pinMode(pl3o,OUTPUT);
pinMode(pl4o,OUTPUT);
pinMode(pl5o,OUTPUT);
pinMode(pl6o,OUTPUT);

pinMode(pl1i,INPUT_PULLUP);
pinMode(pl2i,INPUT_PULLUP);
pinMode(pl3i,INPUT_PULLUP);
pinMode(pl4i,INPUT_PULLUP);
pinMode(pl5i,INPUT_PULLUP);
pinMode(pl6i,INPUT_PULLUP);

    pinMode(A0,INPUT_PULLUP);
    pinMode(A1,INPUT_PULLUP);

  //  Serial.begin(9600);
} 

int stt=1;
void Lighton(){
    int stl,i;
    time=millis();
    
    if(stt==1){
        time0=millis();
        power=1;
        stt=0;
    }
    
    timed=abs(time-time0);
   
    if(timed>=0&&timed<900){
        if((timed%10)==0){
        power=power+pch;
        }
        if(power>=highpower){
            power=highpower;
        }
    }

    else if(timed>=900&&timed<1200){
        
         if((timed%5)==0){
        power=power-pch;
        }
        if(power<=5){
            power=5;
        }      
        
    }
    else{
        stt=1;
    }
            analogWrite(pl1o,power);
            analogWrite(pl2o,power);
            analogWrite(pl3o,power);
            analogWrite(pl4o,power);
            analogWrite(pl5o,power);
            analogWrite(pl6o,power);
}


void Outputs(){

          //  first=6;

 switch(first){
   case 1:{
    analogWrite(pl1o,mpower);
     analogWrite(pl3o,0);
            analogWrite(pl2o,0);
            analogWrite(pl4o,0);
            analogWrite(pl5o,0);
            analogWrite(pl6o,0);
    break;
   }
   case 2:{
    analogWrite(pl2o,mpower);
    analogWrite(pl1o,0);
            analogWrite(pl3o,0);
            analogWrite(pl4o,0);
            analogWrite(pl5o,0);
            analogWrite(pl6o,0);
    break;
   }
   case 3:{
    analogWrite(pl3o,mpower);
     analogWrite(pl1o,0);
            analogWrite(pl2o,0);
            analogWrite(pl4o,0);
            analogWrite(pl5o,0);
            analogWrite(pl6o,0);
    break;
   }
   case 4:{
    analogWrite(pl4o,mpower);
     analogWrite(pl1o,0);
            analogWrite(pl2o,0);
            analogWrite(pl3o,0);
            analogWrite(pl5o,0);
            analogWrite(pl6o,0);
    break;
   }
   case 5:{
    analogWrite(pl5o,mpower);
     analogWrite(pl1o,0);
            analogWrite(pl2o,0);
            analogWrite(pl4o,0);
            analogWrite(pl3o,0);
            analogWrite(pl6o,0);
    break;
   }
   case 6:{
    analogWrite(pl6o,mpower);
     analogWrite(pl1o,0);
            analogWrite(pl2o,0);
            analogWrite(pl4o,0);
            analogWrite(pl5o,0);
            analogWrite(pl3o,0);
    break;
   }
   default:{
    analogWrite(pl1o,mpower);
    analogWrite(pl2o,mpower);
    analogWrite(pl3o,mpower);
    analogWrite(pl4o,mpower);
    analogWrite(pl5o,mpower);
    analogWrite(pl6o,mpower);
   // break;
   }
 }
 delay(2500);
}

void errs(){
    analogWrite(pl1o,mpower);
    analogWrite(pl2o,mpower);
    analogWrite(pl3o,mpower);
    analogWrite(pl4o,mpower);
    analogWrite(pl5o,mpower);
    analogWrite(pl6o,mpower);
}

int Choose(){
   int s1,s2,s3,s4,s5,s6;
    s1=digitalRead(pl1i);
    s2=digitalRead(pl2i);
    s3=digitalRead(pl3i);
    s4=digitalRead(pl4i);
    s5=digitalRead(pl5i);
    s6=digitalRead(pl6i);
  if(go1==1){
    if(s1==LOW){
     key=1;
     first = 1;
    
    }
  }
  if(go2==1){
    if(s2==LOW){
     key=1;
     first= 2;
    // goto yyy;
    }
  }
  if(go3==1){
    if(s3==LOW){
     key=1;
     first= 3;
    // goto yyy;
    }
  }
  if(go4==1){
    if(s4==LOW){
     key=1;
     first= 4;
    // goto yyy;
    }
  }
  if(go5==1){
    if(s5==LOW){
     key=1;
     first= 5;
    // goto yyy;
    }
  }
  if(go6==1){
    if(s6==LOW){
     key=1;
     first= 6;
   //  goto yyy;
    }
  }
   
}


void loop(){
    int state1,state2,va,vb;
    va=analogRead(A0);
    vb=analogRead(A1);

  //  Serial.println(first);

    if(va>=300){
        state1=0;
    }
    else{
        state1=1;
    }

    if(vb>=300){
        state2=0;
    }
    else{
        state2=1;
    }

    if(state1==0&&state2==0){    //都不压
        Lighton();
        go1=0;go2=0;go3=0;go4=0;go5=0;go6=0;
        skey1=0,skey2=0,skey3=0,skey4=0,skey5=0,skey6=0; 
    }
    else if(state1==0&&state2==1){  //开始抢答
    analogWrite(pl1o,mpower);
    analogWrite(pl2o,mpower);
    analogWrite(pl3o,mpower);
    analogWrite(pl4o,mpower);
    analogWrite(pl5o,mpower);
    analogWrite(pl6o,mpower);
       int s1,s2,s3,s4,s5,s6;
       
       s1=digitalRead(pl1i);
       s2=digitalRead(pl2i);
       s3=digitalRead(pl3i);
       s4=digitalRead(pl4i);
       s5=digitalRead(pl5i);
       s6=digitalRead(pl6i);
      
       
    //这一段有bug：
       
       if(skey1==0){
        if(s1==HIGH){
         go1=1;
        }else{skey1=1;}
       }


       
       if(skey2==0){
        if(s2==HIGH){
         go2=1;
        }else{skey2=1;}
       }
       if(skey3==0){
        if(s3==HIGH){
         go3=1;
        }else{skey3=1;}
       }
       if(skey4==0){
        if(s4==HIGH){
         go4=1;
        }else{skey4=1;}
       }
       if(skey5==0){
        if(s5==HIGH){
         go5=1;
        }else{skey5=1;}
       }
       if(skey6==0){
        if(s6==HIGH){
         go6=1;
        }else{skey6=1;}
       }
       

       
       if(key==0){
       Choose();
        // key=0;
       }    
       
       if(key==1){
       Outputs();
      // delay(5000);
       key=0;
       }
    }
    else if(state1==1&&state2==0){   //读取
        Outputs();
        go1=0;go2=0;go3=0;go4=0;go5=0;go6=0;
        skey1=0,skey2=0,skey3=0,skey4=0,skey5=0,skey6=0; 
    }
    else{                           //都压
        errs();
        go1=0;go2=0;go3=0;go4=0;go5=0;go6=0;
        skey1=0,skey2=0,skey3=0,skey4=0,skey5=0,skey6=0; 
    }
}
