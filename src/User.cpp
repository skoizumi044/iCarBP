#include <board.h>

void sensorMonitor(int speed, float pGain, float dGain);

void setup() {
}

void loop() {
	int lineL, lineR;		//地面の明るさ 0~4095
	int error;				//左右の明るさの差
	int controlValue;		//変化させるスピード
	int speedL, speedR; 	//実際のスピード
	float pGain, dGain; 	//比例定数、微分定数
    int min_speed = 0;  	//最低速度
    int max_speed = 100;	//最高速度
    int base_speed = 40;	//基礎速度
    int dynamic_speed;		//動的基礎速度
    int toggle_switch = 0;
    int last_error = 0;		//前回の差
    int diff;				//前回と今の差の差

    /* BTN_1を押すまで待つ */
    while (digitalRead(PIN_BTN1) == LOW) {}

    while (1) {
    	//地面の明るさを取得
        lineL = analogRead(PIN_LINE_L);
        lineR = analogRead(PIN_LINE_R);

        //トグルスイッチとスライダーで設定変更
        toggle_switch = analogRead(PIN_TOGGLE);

        switch(toggle_switch){
        	case 0 :
        		pGain = (float)analogRead(PIN_VOLUME) / 100.0f;
        		break;

        	case 1 :
        		dGain = (float)analogRead(PIN_VOLUME) / 50.0f;
        		break;

        	case 2 :
        		base_speed = analogRead(PIN_VOLUME);
        		break;

        	default :
        		break;
        }

        //運転制御
        error = lineL - lineR;  	//偏差 -4095~4095
        diff = error - last_error;	//前回との偏差の差
        last_error = error;			//偏差の前回値を更新

        controlValue = (int)(((float)error * pGain + (float)diff * dGain) / 40.0f);

        //動的基礎速度制御
        dynamic_speed = base_speed - (abs(controlValue) / 2);

        speedL = dynamic_speed - controlValue;
        speedR = dynamic_speed + controlValue;

        if(speedL < min_speed){
        	speedL = min_speed;
        } else if (speedL > max_speed){
        	speedL = max_speed;
        }

        if(speedR < min_speed){
        	speedR = min_speed;
        } else if (speedR > max_speed){
        	speedR = max_speed;
        }

        analogWrite(PIN_MOTOR_L, speedL);
        analogWrite(PIN_MOTOR_R, speedR);

        //モニターに情報を出力
        sensorMonitor(base_speed, pGain, dGain);
    }
}

void sensorMonitor(int speed, float pGain, float dGain){
    static uint32_t lastLcdUpdate = 0;

    /* 50[ms]毎に処理を実行 */
    /* ※早すぎると数字が読み取れなくなるため */
    if ((millis() - lastLcdUpdate) >= 50) {
        lastLcdUpdate = millis();

        LcdDrv_setCursor(0, 0);
        LcdDrv_print("L");
        LcdDrv_setNum(analogRead(PIN_LINE_L), 4);

        LcdDrv_print(" R");
        LcdDrv_setNum(analogRead(PIN_LINE_R), 4);

        LcdDrv_print(" T");
        LcdDrv_setNum(analogRead(PIN_TOGGLE), 1);

        LcdDrv_setCursor(1, 0);
        LcdDrv_print("P");
        LcdDrv_setNum(pGain * 100, 3);

        LcdDrv_print(" D");
        LcdDrv_setNum(dGain * 100, 3);

        LcdDrv_print(" S");
        LcdDrv_setNum(speed, 3);

        LcdDrv_update();
    }
}
