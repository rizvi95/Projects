#include  "stm32f05xxx.h"
#include "Motor_control.h"

unsigned char count = 0;
unsigned char duty_cycleLF = 75; //Left wheel forward
unsigned char duty_cycleLR = 0;  //Left wheel reverse (default 0)
unsigned char duty_cycleRF = 25; //Right wheel forward
unsigned char duty_cycleRR = 0;  //Right wheel reverse

// volatile unsigned char pwm_count=0;
// volatile unsigned char duty_cycleLF=0;
// volatile unsigned char duty_cycleLR=0; 
// volatile unsigned char duty_cycleRF=0;
// volatile unsigned char duty_cycleRR=0; 


// #define Mot1_forward P1_6
// #define Mot1_reverse P1_7
// #define Mot2_forward P1_3
// #define Mot2_reverse P1_4

#define ON 	1
#define OFF 0

//-10 to 10
#define north 0b00000//'a'
#define south 0b00001// 'b'
//10 to 30 
#define NNE 0b00010//'c'//00010
#define NNW 0b00011//'d'//00011
//parameters to change motor driving ratios 
#define NNnum 

//30 to 50
#define NE 0b00100//	'e'//00100
#define NW 0b00101 // 'f'//00101
//parameters to change motor driving ratios 
#define midnum 2
#define middenom 3

//50 to 70 
#define NEE 0b00110 //'g'//00110
#define NWW 0b00111 //'h'//00111
//#define 

//70 to 90
#define east 0b01000  //'i'//01000
#define west 0b01001 //'j'//01001

//south directions: 
//10 to 30 
#define SSE 0b01010//'k'//01010
#define SSW 0b01011 //'l'//01011
//30 to 50
#define SE 	0b01100 //'m'//01100
#define SW  0b01101 //'n'//01101

//50 to 70 
#define SEE 0b01110 //'o'//01110
#define SWW 0b01111 //'p'//01111

int getsn (char * buff, int len)
{
	int j;
	char c;
	
	for(j=0; j<(len-1); j++)
	{
		c=getchar();
		if ( (c=='\n') || (c=='\r') )
		{
			buff[j]=0;
			return j;
		}
		else
		{
			buff[j]=c;
		}
	}
	buff[j]='\0';
	return len;
}

void Timer1ISR(void) 
{
	TIM1_SR &= ~BIT0; // clear update interrupt flag
		
	// pwm_count++;
	// if(pwm_count>100) pwm_count=0;
	
	// Mot1_forward=pwm_count>duty_cycleLF?0:1;
	// Mot1_reverse=pwm_count>duty_cycleLR?0:1;

	// Mot2_forward=pwm_count>duty_cycleRF?0:1;
	// Mot2_reverse=pwm_count>duty_cycleRR?0:1;	
    
    TogglePins(); // toggle the state of the LED every second  
}

void TogglePins(void) 
{    
	if (count == duty_cycleLF) {
		GPIOA_ODR &= ~( BIT4 );
	} 
	
	if (count == duty_cycleLR) {
		GPIOA_ODR &= ~( BIT5 );
	}
	
	if (count == duty_cycleRF) {
		GPIOA_ODR &= ~( BIT6 );
	}
	
	if (count == duty_cycleRR) {
		GPIOA_ODR &= ~( BIT7 );
	}
	
	if (count == 100) {
		GPIOA_ODR |= ( BIT4 | BIT5| BIT6 | BIT7 );
		count = 0;
	} else {
		count++;
	}	
}

//a function that describes going straight
void go_straight(char speed){
				//Let the speed will become the duty of both motors equally
	 			duty_cycleLF=speed;
		 		duty_cycleRF=speed;
		 		duty_cycleLR=0;
		 		duty_cycleRR=0;
		
	 		}

void go_reverse(char speed){
				//Let the speed will become the duty of both motors equally
	 			duty_cycleLF=0;
		 		duty_cycleRF=0;
		 		duty_cycleLR=speed;
		 		duty_cycleRR=speed;
		
	 		}

void turn_west(char speed ){
				//Let the speed will become the duty of both motors equally

	 			duty_cycleLF=0;
		 		duty_cycleRF=speed;
		 		duty_cycleLR=speed;
		 		duty_cycleRR=0;
		
	 		}
void turn_east(char speed){
				//Let the speed will become the duty of both motors equally
	 			duty_cycleLF=speed;
		 		duty_cycleRF=0;
		 		duty_cycleLR=0;
		 		duty_cycleRR=speed;
		
	 		}

void turn_NW(char speed){
				//Let the speed will become the duty of both motors equally
	 			duty_cycleLF=speed/3;
		 		duty_cycleRF=speed*2;
		 		duty_cycleLR=0;
		 		duty_cycleRR=0;
		
	 		}

void turn_NE(char speed){
				//Let the speed will become the duty of both motors equally
	 			duty_cycleLF=speed*2;
		 		duty_cycleRF=speed/3;
		 		duty_cycleLR=0;
		 		duty_cycleRR=0;
	 		}

void turn_NNE(char speed){
				duty_cycleLF=speed;
		 		duty_cycleRF=speed/2;
		 		duty_cycleLR=0;
		 		duty_cycleRR=0;
			}

void turn_NNW(char speed){
				duty_cycleLF=speed/2;
		 		duty_cycleRF=speed;
		 		duty_cycleLR=0;
		 		duty_cycleRR=0;
			}

void turn_NEE(char speed){
				duty_cycleLF=speed;
		 		duty_cycleRF=speed/5;
		 		duty_cycleLR=0;
		 		duty_cycleRR=0;
			}

void turn_NWW(char speed){
				duty_cycleLF=speed/5;
		 		duty_cycleRF=speed;
		 		duty_cycleLR=0;
		 		duty_cycleRR=0;
			}

void turn_SW(char speed){
//Let the speed will become the duty of both motors equally
	duty_cycleLF=0;
	duty_cycleRF=0;
	duty_cycleLR=speed/3;
	duty_cycleRR=speed;

}


void turn_SE(char speed){
				//Let the speed will become the duty of both motors equally
	 			duty_cycleLF=0;
		 		duty_cycleRF=0;
		 		duty_cycleLR=speed;
		 		duty_cycleRR=speed/3;
	 		}

void turn_SSE(char speed){
				duty_cycleLF=0;
		 		duty_cycleRF=0;
		 		duty_cycleLR=speed;
		 		duty_cycleRR=speed/2;
			}

void turn_SSW(char speed){
				duty_cycleLF=0;
		 		duty_cycleRF=0;
		 		duty_cycleLR=speed/2;
		 		duty_cycleRR=speed;
			}

void turn_SEE(char speed){
				duty_cycleLF=0;
		 		duty_cycleRF=0;
		 		duty_cycleLR=speed;
		 		duty_cycleRR=speed/5;
			}

void turn_SWW(char speed){
				duty_cycleLF=0;
		 		duty_cycleRF=0;
		 		duty_cycleLR=speed/5;
		 		duty_cycleRR=speed;
			}


	void stop(){

			duty_cycleLF=0;
			duty_cycleLR=0;
			duty_cycleRF=0;
			duty_cycleRR=0;
			}

void drive(unsigned char speed, unsigned char direction){

			switch(direction){

			case north :
					{
						go_straight(speed);
						//headlight=ON;
						//taillight=OFF;
						break;
					}

			case south: 
				{
					go_reverse(speed);
					//headlight=ON;
					//taillight=ON;
					break;
				}

			case west: 
				{
					turn_west(speed);
					break;
				}

			case east: 
				{
					turn_east(speed);
					break;
				}

			case NW: 
				{
					turn_NW(speed);
					break;

				}

			case NNE: 
				{ 
					turn_NNE(speed);
					break;
					}

			case NNW: 
				{ 
					turn_NNW(speed);
					break;
					}

			case NE: 
				{ 
					turn_NE(speed);
					break;
					}

			case NEE: 
				{ 
					turn_NEE(speed);
					break;
					}

			case NWW: 
				{ 
					turn_NWW(speed);
					break;
					}


			case SW: 
				{
					turn_SW(speed);
					break;

				}

			case SSE: 
				{ 
					turn_SSE(speed);
					break;
					}

			case SSW: 
				{ 
					turn_SSW(speed);
					break;
					}

			case SE: 
				{ 
					turn_SE(speed);
					break;
					}

			case SEE: 
				{ 
					turn_SEE(speed);
					break;
					}

			case SWW: 
				{ 
					turn_SWW(speed);
					break;
					}


			default: 
				{
					stop();
					direction='x';
					break;
				}

		}
}

