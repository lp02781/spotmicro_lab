
void setup() {
 Serial.begin(9600);
 Serial.setTimeout(1);
}
void loop() {
 while (!Serial.available());
 String str;
 String strs[20];
 int StringCount = 0;
 delay(100);
 str = Serial.readString();
 //Serial.print(str);
 while (str.length() > 0){
    int index = str.indexOf('/');
    if (index == -1){
      strs[StringCount++] = str;
      break;
    }
    else{
      strs[StringCount++] = str.substring(0, index);
      str = str.substring(index+1);
    }
 }
 float data_servo = strs[2].toFloat();
 String data_string = "data string :";
 for(int i=0;i<10;i++){
  data_string += strs[i];
  data_string += "/";
 }
 Serial.println(data_string);
}
