#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <wiringPi.h>
#include <softPwm.h>

#define ENCODERA 24
#define ENCODERB 25
#define ENCODERC 20
#define ENCODERD 21
#define ENCODERE 5
#define ENCODERF 6
#define ENC2REV 1336

#define MOTOR1 18
#define MOTOR2 23
#define MOTOR3 12
#define MOTOR4 16
#define MOTOR5 19
#define MOTOR6 25

#define PGAIN 10
#define DGAIN 500
#define IGAIN 1

int encA;
int encB;
int encC;
int encD;
int encE;
int encF;
int encoderPosition1 = 0;
int encoderPosition2 = 0;
int encoderPosition3 = 0;
int xtime;
int ytime;
int ztime;
float readGearPosition1 = 0;
float readGearPosition_before1 = 0;
float readGearPosition2 = 0;
float readGearPosition_before2 = 0;
float readGearPosition3 = 0;
float readGearPosition_before3 = 0;
float readVelocity1;
float readVelocity2;
float readVelocity3;
float referencePosition;
float referencePosition1;
float referencePosition2;
float referencePosition3;
int storageNum;

float Feedback;
float errorPosition_prev;
float errorPosition1;
float errorPosition2;
float errorPosition3;
float errorSum;
double errorDerivate;

float checkTime;
float checkTimeBefore;
float startTime;
double dt = 50;




void funcEncoderA()
{
	encA = digitalRead(ENCODERA);
	encB = digitalRead(ENCODERB);

	if (encA == HIGH)
	{
		if (encB == LOW)
			encoderPosition1++;

		else
			encoderPosition1--;
	}

	else
	{
		if (encB == LOW)
			encoderPosition1--;
		else
			encoderPosition1++;
	}
	readGearPosition1 = (float)encoderPosition1 / ENC2REV;
	errorPosition1 = referencePosition1 - readGearPosition1;
}
void funcEncoderB()
{
	encA = digitalRead(ENCODERA);
	encB = digitalRead(ENCODERB);

	if (encB == HIGH)
	{
		if (encA == LOW)
			encoderPosition1--;

		else
			encoderPosition1++;
	}

	else
	{
		if (encA == LOW)
			encoderPosition1++;

		else
			encoderPosition1--;
	}
	readGearPosition1 = (float)encoderPosition1 / ENC2REV;
	errorPosition1 = referencePosition1 - readGearPosition1;
}
void funcEncoderC()
{
	encC = digitalRead(ENCODERC);
	encD = digitalRead(ENCODERD);

	if (encC == HIGH)
	{
		if (encD == LOW)
			encoderPosition2++;

		else
			encoderPosition2--;
	}

	else
	{
		if (encD == LOW)
			encoderPosition2--;
		else
			encoderPosition2++;
	}
	readGearPosition2 = (float)encoderPosition2 / ENC2REV;
	errorPosition2 = referencePosition2 - readGearPosition2;
}
void funcEncoderD()
{
	encC = digitalRead(ENCODERC);
	encD = digitalRead(ENCODERD);

	if (encC == HIGH)
	{
		if (encD == LOW)
			encoderPosition2--;

		else
			encoderPosition2++;
	}

	else
	{
		if (encD == LOW)
			encoderPosition2++;

		else
			encoderPosition2--;
	}
	readGearPosition2 = (float)encoderPosition2 / ENC2REV;
	errorPosition2 = referencePosition2 - readGearPosition2;
}
void funcEncoderE()
{
	encE = digitalRead(ENCODERE);
	encF = digitalRead(ENCODERF);

	if (encE == HIGH)
	{
		if (encF == LOW)
			encoderPosition3++;

		else
			encoderPosition3--;
	}

	else
	{
		if (encE == LOW)
			encoderPosition3--;
		else
			encoderPosition3++;
	}
	readGearPosition3 = (float)encoderPosition3 / ENC2REV;
	errorPosition3 = referencePosition3 - readGearPosition3;
}
void funcEncoderF()
{
	encE = digitalRead(ENCODERE);
	encF = digitalRead(ENCODERF);

	if (encF == HIGH)
	{
		if (encE == LOW)
			encoderPosition3--;

		else
			encoderPosition3++;
	}

	else
	{
		if (encE == LOW)
			encoderPosition3++;

		else
			encoderPosition3--;
	}
	readGearPosition3 = (float)encoderPosition3 / ENC2REV;
	errorPosition3 = referencePosition3 - readGearPosition3;
}
void funcswitch()
{
	printf("What do you want to pick up storage Number?(1~35)\n");
	scanf("%d", &storageNum);
	switch (storageNum) {
	case 1:
		printf("You select storage 1\n");
		referencePosition1 = -2.165; //x�� ��ǥ��ġ
		xtime = 3000;  //x�� �����ð�
		referencePosition2 = 123; //y�� ��ǥ��ġ
		ytime = 23000;  //y�� �����ð�
		break;
	case 2:
		printf("You select storage 2\n");
		referencePosition1 = 0; //x�� ��ǥ��ġ
		xtime = 0;  //x�� �����ð�
		referencePosition2 = 123; //y�� ��ǥ��ġ
		ytime = 23000;  //y�� �����ð�
		break;
	case 3:
		printf("You select storage 3\n");
		referencePosition1 = 2.165; //x�� ��ǥ��ġ
		xtime = 3000;  //x�� �����ð�
		referencePosition2 = 123; //y�� ��ǥ��ġ
		ytime = 23000;  //y�� �����ð�
		break;
	case 4:
		printf("You select storage 4\n");
		referencePosition1 = 4.330; //x�� ��ǥ��ġ
		xtime = 6000;  //x�� �����ð�
		referencePosition2 = 123; //y�� ��ǥ��ġ
		ytime = 15000;  //y�� �����ð�
		break;
	case 5:
		printf("You select storage 5\n");
		referencePosition1 = 100; //x�� ��ǥ��ġ
		xtime = 6960;  //x�� �����ð�
		referencePosition2 = 450; //y�� ��ǥ��ġ
		ytime = 23260;  //y�� �����ð�
		break;
	case 6:
		printf("You select storage 6\n");
		referencePosition1 = 8.66; //x�� ��ǥ��ġ
		xtime = 1000;  //x�� �����ð�
		referencePosition2 = 123; //y�� ��ǥ��ġ
		ytime = 1000;  //y�� �����ð�
		break;
	case 7:
		printf("You select storage 7\n");
		referencePosition1 = 10.825; //x�� ��ǥ��ġ
		xtime = 1000;  //x�� �����ð�
		referencePosition2 = 123; //y�� ��ǥ��ġ
		ytime = 1000;  //y�� �����ð�
		break;
	case 8:
		printf("You select storage 8\n");
		referencePosition1 = -2.165; //x�� ��ǥ��ġ
		xtime = 1000;  //x�� �����ð�
		referencePosition2 = 82; //y�� ��ǥ��ġ
		ytime = 1000;  //y�� �����ð�
		break;
	case 9:
		printf("You select storage 9\n");
		referencePosition1 = 0; //x�� ��ǥ��ġ
		xtime = 1000;  //x�� �����ð�
		referencePosition2 = 82; //y�� ��ǥ��ġ
		ytime = 1000;  //y�� �����ð�
		break;
	case 10:
		printf("You select storage 10\n");
		referencePosition1 = 2.165; //x�� ��ǥ��ġ
		xtime = 1000;  //x�� �����ð�
		referencePosition2 = 82; //y�� ��ǥ��ġ
		ytime = 1000;  //y�� �����ð�
		break;
	case 11:
		printf("You select storage 11\n");
		referencePosition1 = 4.330; //x�� ��ǥ��ġ
		xtime = 1000;  //x�� �����ð�
		referencePosition2 = 82; //y�� ��ǥ��ġ
		ytime = 1000;  //y�� �����ð�
		break;
	case 12:
		printf("You select storage 12\n");
		referencePosition1 = 6.495; //x�� ��ǥ��ġ
		xtime = 1000;  //x�� �����ð�
		referencePosition2 = 82; //y�� ��ǥ��ġ
		ytime = 1000;  //y�� �����ð�
		break;
	case 13:
		printf("You select storage 13\n");
		referencePosition1 = 8.660; //x�� ��ǥ��ġ
		xtime = 1000;  //x�� �����ð�
		referencePosition2 = 82; //y�� ��ǥ��ġ
		ytime = 1000;  //y�� �����ð�
		break;
	case 14:
		printf("You select storage 14\n");
		referencePosition1 = 10.825; //x�� ��ǥ��ġ
		xtime = 1000;  //x�� �����ð�
		referencePosition2 = 82; //y�� ��ǥ��ġ
		ytime = 1000;  //y�� �����ð�
		break;
	case 15:
		printf("You select storage 15\n");
		referencePosition1 = -2.165; //x�� ��ǥ��ġ
		xtime = 1000;  //x�� �����ð�
		referencePosition2 = 41; //y�� ��ǥ��ġ
		ytime = 1000;  //y�� �����ð�
		break;
	case 16:
		printf("You select storage 16\n");
		referencePosition1 = 0; //x�� ��ǥ��ġ
		xtime = 1000;  //x�� �����ð�
		referencePosition2 = 41; //y�� ��ǥ��ġ
		ytime = 1000;  //y�� �����ð�
		break;
	case 17:
		printf("You select storage 17\n");
		referencePosition1 = 2.165; //x�� ��ǥ��ġ
		xtime = 1000;  //x�� �����ð�
		referencePosition2 = 41; //y�� ��ǥ��ġ
		ytime = 1000;  //y�� �����ð�
		break;
	case 18:
		printf("You select storage 18\n");
		referencePosition1 = 4.330; //x�� ��ǥ��ġ
		xtime = 1000;  //x�� �����ð�
		referencePosition2 = 41; //y�� ��ǥ��ġ
		ytime = 1000;  //y�� �����ð�
		break;
	case 19:
		printf("You select storage 19\n");
		referencePosition1 = 6.495; //x�� ��ǥ��ġ
		xtime = 1000;  //x�� �����ð�
		referencePosition2 = 41; //y�� ��ǥ��ġ
		ytime = 1000;  //y�� �����ð�
		break;
	case 20:
		printf("You select storage 20\n");
		referencePosition1 = 8.660; //x�� ��ǥ��ġ
		xtime = 1000;  //x�� �����ð�
		referencePosition2 = 41; //y�� ��ǥ��ġ
		ytime = 1000;  //y�� �����ð�
		break;
	case 21:
		printf("You select storage 21\n");
		referencePosition1 = 10.825; //x�� ��ǥ��ġ
		xtime = 1000;  //x�� �����ð�
		referencePosition2 = 41; //y�� ��ǥ��ġ
		ytime = 1000;  //y�� �����ð�
		break;
	case 22:
		printf("You select storage 22\n");
		referencePosition1 = -2.165; //x�� ��ǥ��ġ
		xtime = 1000;  //x�� �����ð�
		referencePosition2 = 0; //y�� ��ǥ��ġ
		ytime = 1000;  //y�� �����ð�
		break;
	case 23:
		printf("You select storage 23\n");
		referencePosition1 = 0; //x�� ��ǥ��ġ
		xtime = 1000;  //x�� �����ð�
		referencePosition2 = 0; //y�� ��ǥ��ġ
		ytime = 1000;  //y�� �����ð�
		break;
	case 24:
		printf("You select storage 24\n");
		referencePosition1 = 2.165; //x�� ��ǥ��ġ
		xtime = 1000;  //x�� �����ð�
		referencePosition2 = 0; //y�� ��ǥ��ġ
		ytime = 1000;  //y�� �����ð�
		break;
	case 25:
		printf("You select storage 25\n");
		referencePosition1 = 4.330; //x�� ��ǥ��ġ
		xtime = 1000;  //x�� �����ð�
		referencePosition2 = 0; //y�� ��ǥ��ġ
		ytime = 1000;  //y�� �����ð�
		break;
	case 26:
		printf("You select storage 26\n");
		referencePosition1 = 6.495; //x�� ��ǥ��ġ
		xtime = 1000;  //x�� �����ð�
		referencePosition2 = 0; //y�� ��ǥ��ġ
		ytime = 1000;  //y�� �����ð�
		break;
	case 27:
		printf("You select storage 27\n");
		referencePosition1 = 8.660; //x�� ��ǥ��ġ
		xtime = 1000;  //x�� �����ð�
		referencePosition2 = 0; //y�� ��ǥ��ġ
		ytime = 1000;  //y�� �����ð�
		break;
	case 28:
		printf("You select storage 28\n");
		referencePosition1 = 10.825; //x�� ��ǥ��ġ
		xtime = 1000;  //x�� �����ð�
		referencePosition2 = 0; //y�� ��ǥ��ġ
		ytime = 1000;  //y�� �����ð�
		break;
	case 29:
		printf("You select storage 29\n");
		referencePosition1 = -2.165; //x�� ��ǥ��ġ
		xtime = 1000;  //x�� �����ð�
		referencePosition2 = -41; //y�� ��ǥ��ġ
		ytime = 1000;  //y�� �����ð�
		break;
	case 30:
		printf("You select storage 30\n");
		referencePosition1 = 0; //x�� ��ǥ��ġ
		xtime = 1000;  //x�� �����ð�
		referencePosition2 = -41; //y�� ��ǥ��ġ
		ytime = 1000;  //y�� �����ð�
		break;
	case 31:
		printf("You select storage 31\n");
		referencePosition1 = 2.165; //x�� ��ǥ��ġ
		xtime = 1000;  //x�� �����ð�
		referencePosition2 = -41; //y�� ��ǥ��ġ
		ytime = 1000;  //y�� �����ð�
		break;
	case 32:
		printf("You select storage 32\n");
		referencePosition1 = 4.330; //x�� ��ǥ��ġ
		xtime = 1000;  //x�� �����ð�
		referencePosition2 = -41; //y�� ��ǥ��ġ
		ytime = 1000;  //y�� �����ð�
		break;
	case 33:
		printf("You select storage 33\n");
		referencePosition1 = 6.495; //x�� ��ǥ��ġ
		xtime = 1000;  //x�� �����ð�
		referencePosition2 = -41; //y�� ��ǥ��ġ
		ytime = 1000;  //y�� �����ð�
		break;
	case 34:
		printf("You select storage 34\n");
		referencePosition1 = 8.660; //x�� ��ǥ��ġ
		xtime = 9000;  //x�� �����ð�
		referencePosition2 = -41; //y�� ��ǥ��ġ
		ytime = 7000;  //y�� �����ð�
		break;
	case 35:
		printf("You select storage 35\n");
		referencePosition1 = 10.825; //x�� ��ǥ��ġ
		xtime = 12000;  //x�� �����ð�
		referencePosition2 = -41; //y�� ��ǥ��ġ
		ytime = 7000;  //y�� �����ð�
		break;


	default:
		printf("Wrong select.\n");
		funcswitch();
	}
}
int main(void)
{
	startTime = millis();
	wiringPiSetupGpio();

	pinMode(ENCODERA, INPUT);
	pinMode(ENCODERB, INPUT);
	pinMode(ENCODERC, INPUT);
	pinMode(ENCODERD, INPUT);
	pinMode(ENCODERE, INPUT);
	pinMode(ENCODERF, INPUT);

	softPwmCreate(MOTOR1, 0, 100);
	softPwmCreate(MOTOR2, 0, 100);
	softPwmCreate(MOTOR3, 0, 100);
	softPwmCreate(MOTOR4, 0, 100);
	softPwmCreate(MOTOR5, 0, 100);
	softPwmCreate(MOTOR6, 0, 100);

	wiringPiISR(ENCODERA, INT_EDGE_BOTH, funcEncoderA);
	wiringPiISR(ENCODERB, INT_EDGE_BOTH, funcEncoderB);
	wiringPiISR(ENCODERC, INT_EDGE_BOTH, funcEncoderC);
	wiringPiISR(ENCODERD, INT_EDGE_BOTH, funcEncoderD);
	wiringPiISR(ENCODERE, INT_EDGE_BOTH, funcEncoderE);
	wiringPiISR(ENCODERF, INT_EDGE_BOTH, funcEncoderF);

	FILE* fp1 = fopen("/home/pi/Desktop/test/matlab/x_axis.txt", "w");
	fclose(fp1);
	FILE* fp2 = fopen("/home/pi/Desktop/test/matlab/y_axis.txt", "w");
	fclose(fp2);
	FILE* fp3 = fopen("/home/pi/Desktop/test/matlab/z_axis.txt", "w");
	fclose(fp3);
	FILE* fp4 = fopen("/home/pi/Desktop/test/matlab/y_axis_reverse.txt", "w");
	fclose(fp4);
	FILE* fp5 = fopen("/home/pi/Desktop/test/matlab/x_axis_reverse.txt", "w");
	fclose(fp5);

	funcswitch();
	referencePosition3 = 300; //z�� ��ǥ��ġ
	ztime = 8500;           //z�� �����ð�

	startTime = millis();   //���� ���� ���� �ð��� ���
	fopen("/home/pi/Desktop/test/matlab/x_axis.txt", "a");
	int recordTime;
	errorPosition_prev = errorPosition1;
	errorPosition1 = referencePosition1 - readGearPosition1;
	errorPosition2 = referencePosition2 - readGearPosition2;
	errorPosition3 = referencePosition3 - readGearPosition3;


	while (checkTime - startTime <= xtime)// x�� �����ð� ���� �۵�
	{
		checkTime = millis();
		recordTime = millis() - startTime;
		readVelocity1 = (readGearPosition1 - readGearPosition_before1) * 1000 / dt;   //������ ȸ���ӵ� ���� ������ rev/s
		if ((checkTime - checkTimeBefore) >= dt)  // 0.05s�� �ѹ� �ڵ尡 �����

		{
			if (errorPosition1 >= 0) // �ð���� �۵�
			{
				errorSum += errorPosition1 * dt / 1000;
				errorDerivate = (errorPosition1 - errorPosition_prev) / dt;
				Feedback = fabs(PGAIN * errorPosition1 + IGAIN * errorSum + DGAIN * errorDerivate); //PID ���
				softPwmWrite(MOTOR1, Feedback);
				softPwmWrite(MOTOR2, 0);
				checkTimeBefore = checkTime;
				readGearPosition_before1 = readGearPosition1;
				printf("(+) Velocity:%f dt:%lf Gearposition: %f Feedback:%f ErrorPos:%f\n", readVelocity1, dt, readGearPosition1, Feedback, errorPosition1); //�ǽð� ���� ���� ���
				fprintf(fp1, "%d   %f\n", recordTime, readGearPosition1);
				errorPosition_prev = errorPosition1;
			}
			if (errorPosition1 < 0) // �ݽð���� �۵�
			{
				errorSum += errorPosition1 * dt / 1000;
				errorDerivate = (errorPosition1 - errorPosition_prev) / dt;
				Feedback = fabs(PGAIN * errorPosition1 + IGAIN * errorSum + DGAIN * errorDerivate); //PID ���
				softPwmWrite(MOTOR1, 0);
				softPwmWrite(MOTOR2, Feedback);
				checkTimeBefore = checkTime;
				readGearPosition_before1 = readGearPosition1;
				printf("(+) Velocity:%f dt:%lf Gearposition: %f Feedback:%f ErrorPos:%f\n", readVelocity1, dt, readGearPosition1, Feedback, errorPosition1); //�ǽð� ���� ���� ���
				fprintf(fp1, "%d   %f\n", recordTime, readGearPosition1);
				errorPosition_prev = errorPosition1;
			}
		}

	}
	softPwmWrite(MOTOR1, 0);
	softPwmWrite(MOTOR2, 0);
	delay(500);
	fclose(fp1);
	//y�� �̵����� �ʱ�ȭ
	startTime = millis();
	errorSum = 0;
	errorDerivate = 0;
	errorPosition_prev = errorPosition2;

	fopen("/home/pi/Desktop/test/matlab/y_axis.txt", "a");
	while (checkTime - startTime <= ytime) //y�� �����ð� ���� �۵�.
	{
		checkTime = millis();
		readVelocity2 = (readGearPosition2 - readGearPosition_before2) * 1000 / dt;   //������ ȸ���ӵ� ���� ������ rev/s
		recordTime = millis() - startTime;
		if ((checkTime - checkTimeBefore) >= dt)  // 0.05s�� �ѹ� �ڵ尡 �����

		{
			if (errorPosition2 >= 0) // �ð���� �۵�
			{
				errorSum += errorPosition2 * dt / 1000;
				errorDerivate = (errorPosition2 - errorPosition_prev) / dt;
				Feedback = fabs(PGAIN * errorPosition2 + IGAIN * errorSum + DGAIN * errorDerivate); //PID ���
				softPwmWrite(MOTOR3, Feedback);
				softPwmWrite(MOTOR4, 0);
				checkTimeBefore = checkTime;
				readGearPosition_before2 = readGearPosition2;
				printf("(+) Velocity:%f dt:%lf Gearposition: %f Feedback:%f ErrorPos:%f I:%f\n", readVelocity2, dt, readGearPosition2, Feedback, errorPosition2); //�ǽð� ���� ���� ���
				fprintf(fp2, "%d   %f   %f\n", recordTime, readGearPosition2, readVelocity2); // �ð�, ��ġ, �ӵ� ���
				errorPosition_prev = errorPosition2;
			}
			if (errorPosition2 < 0) // �ݽð���� �۵�
			{
				errorSum += errorPosition2 * dt / 1000;
				errorDerivate = (errorPosition2 - errorPosition_prev) / dt;
				Feedback = fabs(PGAIN * errorPosition2 + IGAIN * errorSum + DGAIN * errorDerivate); //PID ���
				softPwmWrite(MOTOR3, 0);
				softPwmWrite(MOTOR4, Feedback);
				checkTimeBefore = checkTime;
				readGearPosition_before2 = readGearPosition2;
				printf("(+) Velocity:%f dt:%lf Gearposition: %f Feedback:%f ErrorPos:%f I:%f\n", readVelocity2, dt, readGearPosition2, Feedback, errorPosition2); //�ǽð� ���� ���� ���
				fprintf(fp2, "%d   %f   %f\n", recordTime, readGearPosition2, readVelocity2); // �ð�, ��ġ, �ӵ� ���
				errorPosition_prev = errorPosition2;
			}
		}

	}
	softPwmWrite(MOTOR3, 0);
	softPwmWrite(MOTOR4, 0);
	delay(500);
	fclose(fp2);
	startTime = millis();
	errorSum = 0;
	errorDerivate = 0;
	errorPosition_prev = errorPosition3;

	fopen("/home/pi/Desktop/test/matlab/z_axis.txt", "a");

	while (checkTime - startTime <= ztime)
	{
		checkTime = millis();
		readVelocity3 = (readGearPosition3 - readGearPosition_before3) * 1000 / dt;   //������ ȸ���ӵ� ���� ������ rev/s
		recordTime = millis() - startTime;
		if ((checkTime - checkTimeBefore) >= dt)  // 0.05s�� �ѹ� �ڵ尡 �����

		{
			if (errorPosition3 >= 0) // �ð���� �۵�
			{
				errorSum += errorPosition3 * dt / 1000;
				errorDerivate = (errorPosition3 - errorPosition_prev) / dt;
				Feedback = fabs(PGAIN * errorPosition3 + IGAIN * errorSum + DGAIN * errorDerivate); //PID ���
				softPwmWrite(MOTOR5, Feedback);
				softPwmWrite(MOTOR6, 0);
				checkTimeBefore = checkTime;
				readGearPosition_before3 = readGearPosition3;
				printf("(+) Velocity:%f dt:%lf Gearposition: %f Feedback:%f ErrorPos:%f I:%f\n", readVelocity3, dt, readGearPosition3, Feedback, errorPosition3); //�ǽð� ���� ���� ���
				fprintf(fp3, "%d   %f\n", recordTime, readGearPosition3);
				errorPosition_prev = errorPosition3;
			}
			if (errorPosition3 < 0) // �ݽð���� �۵�
			{
				errorSum += errorPosition3 * dt / 1000;
				errorDerivate = (errorPosition3 - errorPosition_prev) / dt;
				Feedback = fabs(PGAIN * errorPosition3 + IGAIN * errorSum + DGAIN * errorDerivate); //PID ���
				softPwmWrite(MOTOR5, 0);
				softPwmWrite(MOTOR6, Feedback);
				checkTimeBefore = checkTime;
				readGearPosition_before3 = readGearPosition3;
				printf("(+) Velocity:%f dt:%lf Gearposition: %f Feedback:%f ErrorPos:%f I:%f\n", readVelocity3, dt, readGearPosition3, Feedback, errorPosition3); //�ǽð� ���� ���� ���
				fprintf(fp3, "%d   %f\n", recordTime, readGearPosition3);
				errorPosition_prev = errorPosition3;
			}
		}

	}

	softPwmWrite(MOTOR5, 0);
	softPwmWrite(MOTOR6, 0);
	delay(500);
	softPwmWrite(MOTOR3, 40);
	softPwmWrite(MOTOR4, 0);
	delay(1000);

	softPwmWrite(MOTOR3, 0);
	softPwmWrite(MOTOR4, 0);

	referencePosition1 = 0;
	referencePosition2 = 0;
	referencePosition3 = 0;
	errorPosition1 = referencePosition1 - readGearPosition1;
	errorPosition2 = referencePosition2 - readGearPosition2;
	errorPosition3 = referencePosition3 - readGearPosition3;
	errorSum = 0;
	errorDerivate = 0;
	int startTime2 = millis();
	while (checkTime - startTime2 <= ztime)
	{
		checkTime = millis();
		readVelocity3 = (readGearPosition3 - readGearPosition_before3) * 1000 / dt;   //������ ȸ���ӵ� ���� ������ rev/s
		recordTime = millis() - startTime;
		if ((checkTime - checkTimeBefore) >= dt)  // 0.05s�� �ѹ� �ڵ尡 �����

		{
			if (errorPosition3 >= 0) // �ð���� �۵�
			{
				errorSum += errorPosition3 * dt / 1000;
				errorDerivate = (errorPosition3 - errorPosition_prev) / dt;
				Feedback = fabs(PGAIN * errorPosition3 + IGAIN * errorSum + DGAIN * errorDerivate); //PID ���
				softPwmWrite(MOTOR5, Feedback);
				softPwmWrite(MOTOR6, 0);
				checkTimeBefore = checkTime;
				readGearPosition_before3 = readGearPosition3;
				printf("(+) Velocity:%f dt:%lf Gearposition: %f Feedback:%f ErrorPos:%f I:%f\n", readVelocity3, dt, readGearPosition3, Feedback, errorPosition3); //�ǽð� ���� ���� ���
				fprintf(fp3, "%d   %f\n", recordTime, readGearPosition3);
				errorPosition_prev = errorPosition3;
			}
			if (errorPosition3 < 0) // �ݽð���� �۵�
			{
				errorSum += errorPosition3 * dt / 1000;
				errorDerivate = (errorPosition3 - errorPosition_prev) / dt;
				Feedback = fabs(PGAIN * errorPosition3 + IGAIN * errorSum + DGAIN * errorDerivate); //PID ���
				softPwmWrite(MOTOR5, 0);
				softPwmWrite(MOTOR6, Feedback);
				checkTimeBefore = checkTime;
				readGearPosition_before3 = readGearPosition3;
				printf("(+) Velocity:%f dt:%lf Gearposition: %f Feedback:%f ErrorPos:%f I:%f\n", readVelocity3, dt, readGearPosition3, Feedback, errorPosition3); //�ǽð� ���� ���� ���
				fprintf(fp3, "%d   %f\n", recordTime, readGearPosition3);
				errorPosition_prev = errorPosition3;
			}
		}

	}
	softPwmWrite(MOTOR5, 0);
	softPwmWrite(MOTOR6, 0);
	delay(500);
	fclose(fp3);

	errorSum = 0;
	errorDerivate = 0;
	errorPosition_prev = 0;
	startTime = millis();
	fopen("/home/pi/Desktop/test/matlab/y_axis_reverse.txt", "a");
	while (checkTime - startTime <= ytime)
	{
		checkTime = millis();
		readVelocity2 = (readGearPosition2 - readGearPosition_before2) * 1000 / dt;   //������ ȸ���ӵ� ���� ������ rev/s
		recordTime = millis() - startTime;
		if ((checkTime - checkTimeBefore) >= dt)  // 0.05s�� �ѹ� �ڵ尡 �����

		{
			if (errorPosition2 >= 0) // �ð���� �۵�
			{
				errorSum += errorPosition2 * dt / 1000;
				errorDerivate = (errorPosition2 - errorPosition_prev) / dt;
				Feedback = fabs(PGAIN * errorPosition2 + IGAIN * errorSum + DGAIN * errorDerivate); //PID ���
				softPwmWrite(MOTOR3, Feedback);
				softPwmWrite(MOTOR4, 0);
				checkTimeBefore = checkTime;
				readGearPosition_before2 = readGearPosition2;
				printf("(+) Velocity:%f dt:%lf Gearposition: %f Feedback:%f ErrorPos:%f I:%f\n", readVelocity2, dt, readGearPosition2, Feedback, errorPosition2); //�ǽð� ���� ���� ���
				fprintf(fp4, "%d   %f\n", recordTime, readGearPosition2);
				errorPosition_prev = errorPosition2;
			}
			if (errorPosition2 < 0) // �ݽð���� �۵�
			{
				errorSum += errorPosition2 * dt / 1000;
				errorDerivate = (errorPosition2 - errorPosition_prev) / dt;
				Feedback = fabs(PGAIN * errorPosition2 + IGAIN * errorSum + DGAIN * errorDerivate); //PID ���
				softPwmWrite(MOTOR3, 0);
				softPwmWrite(MOTOR4, Feedback);
				checkTimeBefore = checkTime;
				readGearPosition_before2 = readGearPosition2;
				printf("(+) Velocity:%f dt:%lf Gearposition: %f Feedback:%f ErrorPos:%f I:%f\n", readVelocity2, dt, readGearPosition2, Feedback, errorPosition2); //�ǽð� ���� ���� ���
				fprintf(fp4, "%d   %f\n", recordTime, readGearPosition2);
				errorPosition_prev = errorPosition2;
			}
		}

	}
	softPwmWrite(MOTOR3, 0);
	softPwmWrite(MOTOR4, 0);
	delay(500);
	fclose(fp4);

	errorSum = 0;
	errorDerivate = 0;
	errorPosition_prev = 0;
	startTime = millis();
	fopen("/home/pi/Desktop/test/matlab/x_axis_reverse.txt", "a");

	while (checkTime - startTime <= xtime)
	{
		checkTime = millis();
		recordTime = millis() - startTime;
		readVelocity1 = (readGearPosition1 - readGearPosition_before1) * 1000 / dt;   //������ ȸ���ӵ� ���� ������ rev/s
		if ((checkTime - checkTimeBefore) >= dt)  // 0.05s�� �ѹ� �ڵ尡 �����

		{
			if (errorPosition1 >= 0) // �ð���� �۵�
			{
				errorSum += errorPosition1 * dt / 1000;
				errorDerivate = (errorPosition1 - errorPosition_prev) / dt;
				Feedback = fabs(PGAIN * errorPosition1 + IGAIN * errorSum + DGAIN * errorDerivate); //PID ���
				softPwmWrite(MOTOR1, Feedback);
				softPwmWrite(MOTOR2, 0);
				checkTimeBefore = checkTime;
				readGearPosition_before1 = readGearPosition1;
				printf("(+) Velocity:%f dt:%lf Gearposition: %f Feedback:%f ErrorPos:%f\n", readVelocity1, dt, readGearPosition1, Feedback, errorPosition1); //�ǽð� ���� ���� ���
				fprintf(fp5, "%d   %f   %f\n", recordTime, readGearPosition1, readVelocity1);
				errorPosition_prev = errorPosition1;
			}
			if (errorPosition1 < 0) // �ݽð���� �۵�
			{
				errorSum += errorPosition1 * dt / 1000;
				errorDerivate = (errorPosition1 - errorPosition_prev) / dt;
				Feedback = fabs(PGAIN * errorPosition1 + IGAIN * errorSum + DGAIN * errorDerivate); //PID ���
				softPwmWrite(MOTOR1, 0);
				softPwmWrite(MOTOR2, Feedback);
				checkTimeBefore = checkTime;
				readGearPosition_before1 = readGearPosition1;
				printf("(+) Velocity:%f dt:%lf Gearposition: %f Feedback:%f ErrorPos:%f\n", readVelocity1, dt, readGearPosition1, Feedback, errorPosition1); //�ǽð� ���� ���� ���
				fprintf(fp5, "%d   %f\n", recordTime, readGearPosition1);
				errorPosition_prev = errorPosition1;
			}
		}

	}
	softPwmWrite(MOTOR1, 0);
	softPwmWrite(MOTOR2, 0);
	fclose(fp5);

	return 0;
}