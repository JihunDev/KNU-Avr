#include <mega128.h>
#include <delay.h>

char seg_fat[10] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7c, 0x07, 0x7f, 0x67};

void Seg2_out(int, int);

void main(void){
    int num = 60;	//카운터 초기값
    int a,s=0;		//a:카운터 반복문을 위한 변수, s:Score값을 넘기기 위한 변수
    int ad_val;		//센서 값을 받기위한 변수

    DDRB = 0xFF;	
    DDRF = 0x00;	
    DDRE = 0xFF;	
    DDRD = 0b11110000;	
    
    ADMUX=0x02;		//ADC2 단극성입력	
    ADCSRA=0x87;	//ADC enable, 분주비는 128
    delay_ms(0);

    for(a=0;a<=60;a++){
        ADCSRA=0xC7;				//ADEN=1, ADSC=1 변환시작
        while((ADCSRA&0x10)==0);		//ADIF = 1이 될때까지
        ad_val=(int)ADCL + ((int)ADCH << 8);	//ad_val에 데이터 입력
        delay_ms(0);
        if(ad_val <= 200){			//ad_val값 비교
        	PORTE = 0x00;
        	delay_ms(0);
        	s+=2;
        }    
        else{
            PORTE = 0xff;
            delay_ms(0);
        }
    Seg2_out(num, s);
        num--;
        if(num < 0) num = 0;
        
    }
}

void Seg2_out(int num, int s)
{
    int i, N10, N1, S10, S1;

    N10 = num / 10;		//타이머 10의자리
    N1 = num % 10;		//타이머 1의자리
    
    S10 = s / 10;		//스코어 10의자리
    S1 = s % 10;		//스코어 1의 자리

    for(i=0; i<49; i++){             
        PORTD = 0b00010000;	//타이머 10의자리 세그먼트 사용
        PORTB = seg_fat[N10];	//출력값 입력
        delay_ms(5);		
        PORTD = 0b11110000;	//포트 초기화
	
        PORTD = 0b00100000;	
        PORTB = seg_fat[N1];
        delay_ms(5);
        PORTD = 0b11110000;

        PORTD = 0b10000000;	//스코어 1의자리 세그먼트 사용
        PORTB = seg_fat[S1];	//스코어값 입력
        delay_ms(5);
        PORTD = 0b11110000;	//포트 초기화

        PORTD = 0b01000000;
        PORTB = seg_fat[S10];
        delay_ms(5);
        PORTD = 0b11110000;
    
    }
}

