int pos_pins[] = {8,11,12,7}; // 몇번째 세그먼트
int num_of_pos = 4;
int pins[] = {9,13,5,3,2,10,6,4}; // 세그먼트 a, b, c, d, e, f, g, dp
int num_of_pins = 8;
int button = A0;
int buzzerPin = A1;
int delaytime = 5;
int cnt = 0;

bool segment[10][8] = {
  {true, true, true, true, true, true, false, false}, //0
  {false, true, true, false, false, false, false, false}, //1
  {true, true, false, true, true, false, true, false}, //2
  {true, true, true, true, false, false, true, false}, //3
  {false, true, true, false, false, true, true, false}, //4
  {true, false, true, true, false, true, true, false}, //5
  {true, false, true, true, true, true, true, false}, //6
  {true, true, true, false, false, false, false, false}, //7
  {true, true, true, true, true, true, true, false}, //8
  {true, true, true, true, false, true, true, false} //9
};
int data;
void setup() {
  Serial.begin(9600);
  for(int i=0; i<num_of_pos; i++) {
     pinMode(pos_pins[i], OUTPUT);
  }
  for(int i=0; i<num_of_pins; i++) {
    pinMode(pins[i], OUTPUT);
  }
  pinMode(button, INPUT_PULLUP);
  pinMode(buzzerPin, OUTPUT);

}

void loop() {
  while(Serial.available()){
    data = Serial.read();
  }
  if(data == '1'){
    cnt = cnt+1; 
    if(cnt == 10000) cnt = 0;
    tone(buzzerPin, 131);
    delay(150); 
  }
  else{
    noTone(buzzerPin);
  }
  if(digitalRead(button) == LOW){
    cnt=0;
    delay(150); 
  }
  digits_4_seven_segment(cnt);
}

void set_position(int pos){
  for(int i = 0; i < num_of_pos; i++) {
    if(i == pos-1){
      digitalWrite(pos_pins[i], LOW);
    } else {
      digitalWrite(pos_pins[i], HIGH);
    }
  }
}

void set_number(int number){
  for(int i=0;i<num_of_pins;++i){ 
    segment[number][i] ? digitalWrite(pins[i], HIGH) : digitalWrite(pins[i], LOW); 
  }
}

void set_seven_segment(int pos, int number){
  set_position(pos);
  set_number(number);
}

void digits_4_seven_segment(int num){
  for(int i=4;i>0;--i){
    set_seven_segment(i,num%10);
    delay(delaytime);
    num = num/10;
  }
}
