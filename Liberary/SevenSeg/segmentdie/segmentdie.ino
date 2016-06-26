//  _ ___ _______     ___ ___ ___  ___ _   _ ___ _____ ___ 
// / |_  )__ /   \   / __|_ _| _ \/ __| | | |_ _|_   _/ __| 
// | |/ / |_ \ |) | | (__ | ||   / (__| |_| || |  | | \__ \ 
// |_/___|___/___/   \___|___|_|_\\___|\___/|___| |_| |___/ 
// 
// 7-segment die
// 
// Made by Rob Roberts
// License: CC-BY-SA 3.0
// Downloaded from: http://123d.circuits.io/circuits/57256-7-segment-die

int a = 0;
int b = 1;
int c = 2;
int d = 3;
int e = 4;
int f = 5;
int g = 6;

int st = 8;
int gsel = 9;
int zg = 10;
int slp = 11;


// the setup rousdasdastsddffwddifssasasdsdfsdned runs ccxzzcasdasdadsxsaddsadasdasasdonce when you press reset:
void setup() {   
  // initialize the digital pin as an output.
  pinMode(a, OUTPUT);     
  pinMode(b, OUTPUT);     
  pinMode(c, OUTPUT);     
  pinMode(d, OUTPUT);     
  pinMode(e, OUTPUT);     
  pinMode(f, OUTPUT);     
  pinMode(g, OUTPUT);     

  writeDigit(-1);
  
  // Serial.begin(9600);
  pinMode(st, OUTPUT);     
  pinMode(gsel, OUTPUT);     
  pinMode(zg, INPUT);     
  pinMode(slp, OUTPUT);     
  
  digitalWrite(st, LOW);
  digitalWrite(gsel, HIGH);
  digitalWrite(slp, HIGH);
}

void writeDigit(int digit) {
  Serial.print("digit: ");
  Serial.print(digit);
  Serial.print("\n");
  
  switch(digit) {
    case 0:
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, HIGH);
      digitalWrite(f, HIGH);
      digitalWrite(g, LOW);
      break;
    case 1:
      digitalWrite(a, LOW);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, LOW);
      digitalWrite(e, LOW);
      digitalWrite(f, LOW);
      digitalWrite(g, LOW);
      break;
    case 2:
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, LOW);
      digitalWrite(d, HIGH);
      digitalWrite(e, HIGH);
      digitalWrite(f, LOW);
      digitalWrite(g, HIGH);
      break;
    case 3:
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, LOW);
      digitalWrite(f, LOW);
      digitalWrite(g, HIGH);
      break;
    case 4:
      digitalWrite(a, LOW);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, LOW);
      digitalWrite(e, LOW);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
      break;
    case 5:
      digitalWrite(a, HIGH);
      digitalWrite(b, LOW);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, LOW);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
      break;
    case 6:
      digitalWrite(a, HIGH);
      digitalWrite(b, LOW);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, HIGH);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
      break;
    case 7:
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, LOW);
      digitalWrite(e, LOW);
      digitalWrite(f, LOW);
      digitalWrite(g, LOW);
      break;
    case 8:
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, HIGH);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
      break;
    case 9:
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, LOW);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
      break;
    case -1:
      digitalWrite(a, LOW);
      digitalWrite(b, LOW);
      digitalWrite(c, LOW);
      digitalWrite(d, LOW);
      digitalWrite(e, LOW);
      digitalWrite(f, LOW);
      digitalWrite(g, LOW);
      break;
  }
}

int get_g() {
  int x = (analogRead(A0)-337)*5*5*100/1024;
  int y = (analogRead(A1)-337)*5*5*100/1024;
  int z = (analogRead(A2)-337)*5*5*100/1024;
  
  int gf = abs(sqrt(x*x+y*y+z*z)-100);  
  Serial.print("gf: ");
  Serial.println(gf);
  
  return gf;
}

int time = 0;
int digit = 0;

unsigned long seed = 42; 
unsigned long randomer() {
  seed = (1103515245 * seed + 12345) % 2147483648;
  return seed;
}  


int count = 0;
int count2 = 0;

int state = 0;
// 0 = idle
// 1 = shaking
// 2 = show_result

int sum = 0;
int cur = 0;
int res; 

// the loop routine runs over and over again forever:
void loop() {
  cur = get_g();
  sum = randomer();
  
  switch(state) {
    case 0:
      if (cur > 30) {
         state = 1; 
         count = 0;
      }  
      break;
    case 1:
      if (count2 == 10) {
        writeDigit(sum % 6 + 1);
        count2=0;
      } else {
        count2++;
      }  
      if (cur > 30) {
         state = 1; 
         count = 0;
      } else {
        if (count > 20) {
          state = 2;
          count = 0;
        } else {
          count ++;
        }  
      }
      break;
    case 2:
      if (count == 0) writeDigit(sum % 6 + 1);
      if (count == 10) writeDigit(sum % 6 + 1);
      if (count == 25) writeDigit(sum % 6 + 1);
      if (count == 45) writeDigit(sum % 6 + 1);
      if (count == 70) writeDigit(sum % 6 + 1);
      if (count == 100) writeDigit(sum % 6 + 1);
      if (count == 135) {
        res = sum % 6 + 1;
        writeDigit(res);
      }  
      
        
      if (count == 185) writeDigit(-1);
      if (count == 235) writeDigit(res);
      if (count == 285) writeDigit(-1);
      if (count == 335) {
        writeDigit(res);
        state = 0;
        count = 0;        
      }
      count++;  
      break;
  }   
  delay(10);
}
