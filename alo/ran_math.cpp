#include "ran_math.h"
/**
 *����λ����ʵ�ֵļӼ��˳���
 *
 *
 */
//�ӷ�ʵ��
int add(int num1, int num2) {
	int sum = num1 ^ num2;//�����ǽ�һ�ļӷ�����ʹ��������
	int carry = (num1 & num2) << 1;//��һ�Ľ������ʹ�������������һλ�õ�
	while (carry != 0){//��û�н�һʱ�ӷ�����
		//����
		int tempSum = sum ^ carry;
		carry = (sum & carry) << 1;
		sum = tempSum;
	}
	return sum;
}

//����ʵ��
int sub(int num1, int num2) {
	//����ȡ��num2�ĸ��� ������ʾ�������Ĳ���
	int oppositor = add(~num2, 1);
	//����num1+num2����ʹ��num1+(-num2)����ʾ
	return add(num1, oppositor);
}

//�˷�ʵ��
int multip(int num1, int num2) {
	//�������ľ���ֵ
	int absNum1 = num1 < 0 ? add(~num1, 1) : num1;
	int absNum2 = num2 < 0 ? add(~num2, 1) : num2;
	int result = 0;
	/*
	for (int i = 0; i < absNum2; i++) {
		result += absNum1;
	}
	*/
	int multipcand = absNum1;//������ 
	int multiper = absNum2;//����
	while (multiper){
		if (multiper & 0x1) {//������������һλΪ1 �����һ��������
			result = add(result, multipcand);
		}
		multipcand <<= 1;//����������һλ
		multiper >>= 1;//��������һλ
	}
	//�жϷ���
	if ((num1 ^ num2) < 0) {//��ŷ��ظ���
		return add(~result, 1);
	}
	else {
		return result;
	}
}

//����ʵ��
int division(int num1, int num2) {
	// ��ȡ�������ͳ����ľ���ֵ    
	int dividend = num1 > 0 ? num1 : add(~num1, 1);
	int divisor = num2 > 0 ? num2 : add(~num2, 1);
	int quotient = 0;// ��    
	int remainder = 0;// ����    
	for (int i = 31; i >= 0; i--) {
		//�Ƚ�dividend�Ƿ����divisor��(1<<i)�η�����Ҫ��dividend��(divisor<<i)�Ƚϣ�������(dividend>>i)��divisor�Ƚϣ�
		//Ч��һ�������ǿ��Ա�����(divisor<<i)�������ܵ��µ������������������dividend����С��divisor�������������dividend����divisor       
		if ((dividend >> i) >= divisor) {
			quotient = add(quotient, 1 << i);
			dividend = sub(dividend, divisor << i);
		}
	}
	// ȷ���̵ķ���    
	if ((num1 ^ num2) < 0) {
		// ��������ͱ�������ţ�����Ϊ����        
		quotient = add(~quotient, 1);
	}
	// ȷ����������    
	remainder = num2 > 0 ? dividend : add(~dividend, 1);
	return quotient;// ������
}