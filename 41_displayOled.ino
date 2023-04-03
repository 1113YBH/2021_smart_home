// display.setTextSize(2);
// TextSize(1): 6px(가로 21.2글자) x 8px(세로 8줄)
// TextSize(2): 12px(가로 10.7글자) x 16px(세로 4줄)

void updateOled() {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print(temperature, 1); display.print(" 'C   ");
  display.print(humidity, 1); display.println(" %");
  display.print(distance); display.print(" cm   ");
  display.print(cdsValue); display.println(" cds  ");
  display.print("L("); display.print(lampMode); display.print("):"); display.print(isLampOn); display.print(" ");
  display.print("F("); display.print(fanMode); display.print("):"); display.print(isFanOn); display.print(" ");
  display.print("D("); display.print(doorMode); display.print("):"); display.print(isDoorOpen); display.println();
  display.print("Door : ");  display.println(DoorState[doorMode]);
  display.display();
}
