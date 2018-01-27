#include "ran_math.h"
/**
 *基于位运算实现的加减乘除法
 *
 *
 */
//加法实现
int add(int num1, int num2) {
	int sum = num1 ^ num2;//不考虑进一的加法可以使用异或计算
	int carry = (num1 & num2) << 1;//进一的结果可以使用与运算符左移一位得到
	while (carry != 0){//当没有进一时加法结束
		//迭代
		int tempSum = sum ^ carry;
		carry = (sum & carry) << 1;
		sum = tempSum;
	}
	return sum;
}

//减法实现
int sub(int num1, int num2) {
	//首先取得num2的负数 负数表示是正数的补码
	int oppositor = add(~num2, 1);
	//于是num1+num2可以使用num1+(-num2)来表示
	return add(num1, oppositor);
}

//乘法实现
int multip(int num1, int num2) {
	//计算结果的绝对值
	int absNum1 = num1 < 0 ? add(~num1, 1) : num1;
	int absNum2 = num2 < 0 ? add(~num2, 1) : num2;
	int result = 0;
	/*
	for (int i = 0; i < absNum2; i++) {
		result += absNum1;
	}
	*/
	int multipcand = absNum1;//被乘数 
	int multiper = absNum2;//乘数
	while (multiper){
		if (multiper & 0x1) {//如果乘数的最后一位为1 则加上一个被乘数
			result = add(result, multipcand);
		}
		multipcand <<= 1;//被乘数左移一位
		multiper >>= 1;//乘数右移一位
	}
	//判断符号
	if ((num1 ^ num2) < 0) {//异号返回负数
		return add(~result, 1);
	}
	else {
		return result;
	}
}

//除法实现
int division(int num1, int num2) {
	// 先取被除数和除数的绝对值    
	int dividend = num1 > 0 ? num1 : add(~num1, 1);
	int divisor = num2 > 0 ? num2 : add(~num2, 1);
	int quotient = 0;// 商    
	int remainder = 0;// 余数    
	for (int i = 31; i >= 0; i--) {
		//比较dividend是否大于divisor的(1<<i)次方，不要将dividend与(divisor<<i)比较，而是用(dividend>>i)与divisor比较，
		//效果一样，但是可以避免因(divisor<<i)操作可能导致的溢出，如果溢出则会可能dividend本身小于divisor，但是溢出导致dividend大于divisor       
		if ((dividend >> i) >= divisor) {
			quotient = add(quotient, 1 << i);
			dividend = sub(dividend, divisor << i);
		}
	}
	// 确定商的符号    
	if ((num1 ^ num2) < 0) {
		// 如果除数和被除数异号，则商为负数        
		quotient = add(~quotient, 1);
	}
	// 确定余数符号    
	remainder = num2 > 0 ? dividend : add(~dividend, 1);
	return quotient;// 返回商
}