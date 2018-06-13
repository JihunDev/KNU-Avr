#include <mega128.h>
#include <delay.h>

char seg_fat[10] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7c, 0x07, 0x7f, 0x67};

void Seg2_out(int, int);

void main(void){
    int num = 60;	//ī���� �ʱⰪ
    int a,s=0;		//a:ī���� �ݺ����� ���� ����, s:Score���� �ѱ�� ���� ����
    int ad_val;		//���� ���� �ޱ����� ����

    DDRB = 0xFF;	
    DDRF = 0x00;	
    DDRE = 0xFF;	
    DDRD = 0b11110000;	
    
    ADMUX=0x02;		//ADC2 �ܱؼ��Է�	
    ADCSRA=0x87;	//ADC enable, ���ֺ�� 128
    delay_ms(0);

    for(a=0;a<=60;a++){
        ADCSRA=0xC7;				//ADEN=1, ADSC=1 ��ȯ����
        while((ADCSRA&0x10)==0);		//ADIF = 1�� �ɶ�����
        ad_val=(int)ADCL + ((int)ADCH << 8);	//ad_val�� ������ �Է�
        delay_ms(0);
        if(ad_val <= 200){			//ad_val�� ��
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

    N10 = num / 10;		//Ÿ�̸� 10���ڸ�
    N1 = num % 10;		//Ÿ�̸� 1���ڸ�
    
    S10 = s / 10;		//���ھ� 10���ڸ�
    S1 = s % 10;		//���ھ� 1�� �ڸ�

    for(i=0; i<49; i++){             
        PORTD = 0b00010000;	//Ÿ�̸� 10���ڸ� ���׸�Ʈ ���
        PORTB = seg_fat[N10];	//��°� �Է�
        delay_ms(5);		
        PORTD = 0b11110000;	//��Ʈ �ʱ�ȭ
	
        PORTD = 0b00100000;	
        PORTB = seg_fat[N1];
        delay_ms(5);
        PORTD = 0b11110000;

        PORTD = 0b10000000;	//���ھ� 1���ڸ� ���׸�Ʈ ���
        PORTB = seg_fat[S1];	//���ھ �Է�
        delay_ms(5);
        PORTD = 0b11110000;	//��Ʈ �ʱ�ȭ

        PORTD = 0b01000000;
        PORTB = seg_fat[S10];
        delay_ms(5);
        PORTD = 0b11110000;
    
    }
}

