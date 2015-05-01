Java相关技巧
===

- [Java一般操作](#Java一般操作)
- [Java针对大数的操作总结](#Java针对大数的操作总结)

Java一般操作
---

1. 提交格式

```java
import java.util.*;  
public class Main{  
public static void main(String[] args){  
    Scanner cin = new Scanner(System.in));  
    }  
} 
```

2. 输入

```java
cin.hasNext() 或 cin.hasNextInt() 或 cin.hasNextDouble()      // 判断是否有下一个输入可以用
int n = cin.nextInt();   
String s = cin.next();  
double t = cin.nextDouble();  
String s = cin.nextLine();  
```

3. 浮点数输出

```java
DecimalFormat g = new DecimalFormat("0.00");   
double a = 123.45678;  
System.out.println(g.format(a));        // 输出 123.46  
```

4. 简单大数

```java
import java.math.*;     

BigInteger a = BigInteger.valueOf(100000);  
BigInteger b = BigInteger.valueOf(10000);  

System.out.println(a.add(b));  
System.out.println(a.subtract(b));        
System.out.println(a.multiply(b));  
System.out.println(a.divide(b));          
System.out.println(a.mod(b));  
System.out.println(a.compareTo(b));     // 返回值 -1,0,1  
```

5. 字符串

```java
s.substring(a,b);
String a = "0123456789";  
System.out.println(a.substring(2,5));        // 234  
```

6. 数组

```java
int[] a = new int[123];  
Arrays.fill(a,123);           // 相当于memset
System.out.println(a[3]);     // 输出 123  
```


Java针对大数的操作总结
---

- BigInteger：针对大的整数， 是以字符串方式进行传人的
```java
import java.math.BigInteger ; 
public class BigIntegerDemo01{ 
    public static void main(String args[]){ 
        BigInteger bi1 = new BigInteger("123456789") ;  // 声明BigInteger对象 
        BigInteger bi2 = new BigInteger("987654321") ;  // 声明BigInteger对象 
        System.out.println("加法操作：" + bi2.add(bi1)) ;    // 加法操作 
        System.out.println("减法操作：" + bi2.subtract(bi1)) ;   // 减法操作 
        System.out.println("乘法操作：" + bi2.multiply(bi1)) ;   // 乘法操作 
        System.out.println("除法操作：" + bi2.divide(bi1)) ; // 除法操作 
        System.out.println("最大数：" + bi2.max(bi1)) ;  // 求出最大数 
        System.out.println("最小数：" + bi2.min(bi1)) ;  // 求出最小数 
        BigInteger result[] = bi2.divideAndRemainder(bi1) ; // 求出余数的除法操作 
        System.out.println("商是：" + result[0] +  
            "；余数是：" + result[1]) ; 
    } 
}; 
```

```
执行结果：
加法操作：1111111110 
减法操作：864197532 
乘法操作：121932631112635269 
除法操作：8 
最大数：987654321 
最小数：123456789 
商是：8；余数是：9 
```

- BigDecimal：针对大的浮点数， 是以字符串的方式传入的

```java
import java.math.* ; 
class MyMath{ 
    public static double add(double d1,double d2){      // 进行加法计算 
        BigDecimal b1 = new BigDecimal(d1) ; 
        BigDecimal b2 = new BigDecimal(d2) ; 
        return b1.add(b2).doubleValue() ; 
    } 
    public static double sub(double d1,double d2){      // 进行减法计算 
        BigDecimal b1 = new BigDecimal(d1) ; 
        BigDecimal b2 = new BigDecimal(d2) ; 
        return b1.subtract(b2).doubleValue() ; 
    } 
    public static double mul(double d1,double d2){      // 进行乘法计算 
        BigDecimal b1 = new BigDecimal(d1) ; 
        BigDecimal b2 = new BigDecimal(d2) ; 
        return b1.multiply(b2).doubleValue() ; 
    } 
    public static double div(double d1,double d2,int len){      // 进行乘法计算 
        BigDecimal b1 = new BigDecimal(d1) ; 
        BigDecimal b2 = new BigDecimal(d2) ; 
        return b1.divide(b2,len,BigDecimal.ROUND_HALF_UP).doubleValue() ; 
    } 
    public static double round(double d,int len){   // 进行四舍五入 
        BigDecimal b1 = new BigDecimal(d) ; 
        BigDecimal b2 = new BigDecimal(1) ; 
        return b1.divide(b2,len,BigDecimal.ROUND_HALF_UP).doubleValue() ; 
    } 
}; 
 
public class BigDecimalDemo01{ 
    public static void main(String args[]){ 
        System.out.println("加法运算：" + MyMath.round(MyMath.add(10.345,3.333),1)) ; 
        System.out.println("减法运算：" + MyMath.round(MyMath.sub(10.345,3.333),3)) ; 
        System.out.println("乘法运算：" + MyMath.round(MyMath.mul(10.345,3.333),2)) ; 
        System.out.println("除法运算：" + MyMath.div(10.345,3.333,3)) ; 
    } 
}; 

```java
执行结果：
加法运算：13.7 
减法运算：7.012 
乘法运算：34.48 
除法运算：3.104 
总结：针对大数以字符串的方式传人，再利用提供的加减乘除方法来操作数据，而不是以'+ - * /'来操作数据
```
