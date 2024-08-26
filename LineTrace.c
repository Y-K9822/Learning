#define Kp 1.5
#define Kd 0.012
#define Dt 0.01
#define sensor_MAX 8
#define BASE_SPEED 50
#define ERROR_THRESHOLD_1 15
#define ERROR_THRESHOLD_2 25

typedef struct Motor_{
    int speed;
    int direction;
}Motor_t;

static int get_sensor_value(void);
void LeftMotor_setSpeed(int speed);
void RightMotor_setSpeed(int speed);

static int prev_error = 0;
static Motor_t LeftMotor;
static Motor_t RightMotor;

void PD_control(void){
    static int sensorValue[sensor_MAX] = {0};
    sensorValue[sensor_MAX] = get_sensor_value();
    int sensor_left = 0;
    int sensor_right = 0;
    int error = 0;
    int LeftSpeed = 0;
    int RightSpeed = 0;
    int derivative = 0;
    int control = 0;

    for(int i = 0; i < sensor_MAX/2; i++){
        sensor_left += sensorValue[i];
        sensor_right += sensorValue[sensor_MAX - 1 -i];
    }

    error = (sensor_left * 2)/sensor_MAX - (sensor_right * 2)/sensor_MAX;
    if(error <= ERROR_THRESHOLD_1 && error >= -ERROR_THRESHOLD_1){
        error = 0;
        LeftMotor_setSpeed(BASE_SPEED);
        RightMotor_setSpeed(BASE_SPEED);
    }else if(error > ERROR_THRESHOLD_2 || error < -ERROR_THRESHOLD_2){
        LeftSpeed = 1;
        RightSpeed = 1;
        LeftMotor_setSpeed(LeftSpeed);
        RightMotor_setSpeed(RightSpeed);
    }else{
        LeftSpeed = 10;
        RightSpeed = 10;
        LeftMotor_setSpeed(LeftSpeed);
        RightMotor_setSpeed(RightSpeed);
    }

    control = (int)(Kp * error + Kd * (error - prev_error) / Dt);

    LeftSpeed = LeftMotor.speed - control;
    if(LeftSpeed < 10){
        LeftSpeed = 10;
    }

    RightSpeed = RightMotor.speed + control;
    if(RightSpeed < 10){
        RightSpeed = 10;
    }


    LeftMotor_setSpeed(LeftSpeed);
    RightMotor_setSpeed(RightSpeed);
}