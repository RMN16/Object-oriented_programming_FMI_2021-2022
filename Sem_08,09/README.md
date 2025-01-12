# Предефиниране на оператори (Operator overloading)

## Оператори

### Видове оператори:

- *Унарни* (на един аргумент)
- *Бинарни* (на два аргумента)
- *Тернарни* (на три аргумента)

### Характеристика на операторите:

- Приоритет
- Асоциативност
- Позиция на оператора спярмо аргумента - *префиксен* оператор, *инфиксен* оператор, *суфиксен* оператор

### Списък на операторите в C++
![alt_text](https://i.ibb.co/H4CWhHx/Operators-precedence.png)

## Предефиниране на оператори

C++ позволява повечето вградени оператори да могат да бъдат предефинирани така, че да работят за обекти от произволен клас.

Следните оператори **могат** да бъдат предефинирани:
- аритметични (+, -, *, /, %)
- логически (!, &&, ||)
- указателни (&, *, ->, [])
- за сравнение (==, !=, <, >, <=, >=)
- побитови (&, |, ˆ, ˜, <<, >>)
- за присвояване (=, +=, -=, *=, /=, %=, &=, |= , <<=, >>=, ++, --)
- за работа с паметта (new, new[], delete, delete[])
- оператор за изброяване (,)
- оператор за извикване на функция (())
- оператор за преобразуване на тип

Следните оператори **не могат** да бъдат предефинирани:
- тернарен оператор (? :)
- оператор за указване на област (scope resolution operator) (::)
- оператор за избор на член (.)
- оператор за намиране на големина (sizeof)
- препроцесорни оператори (#, ##)

---
:bangbang: При предефинирането на оператор **не могат** да се променят *приоритетът* и *асоциативността* му, както и *броят и позицията на аргументите* му.

---

### Предефиниране на оператори чрез член-функции

- <тип> operator<операция>([<тип>]) [const]
- <тип> <клас>::operator<операция>([<тип> <име>]) [const] { <тяло> }

**Пример:**
```c++
ComplexNumber& ComplexNumber::operator+=(const ComplexNumber& other)
{
	real += other.real;
	im += other.im;
	return *this;
}
```

Така предефинираният оператор+= за работа с комплексни числа ни позволява да правим следното:
```c++
int main()
{
	ComplexNumber c1(5, 10); // c1 = 5 + 10i
	ComplexNumber c2(23, 6); // c2 = 23 + 6i
	c1 += c2; // c1 = 28 + 16i
}
```

### Предефиниране на оператори чрез обикновени функции

- <тип> operator<операция>(<тип1> <име1>) { <тяло> }
- <тип> operator<операция>(<тип1> <име1>, <тип2> <име2>) { <тяло> }

:bangbang: Поне един от <тип1> и <тип2> трябва да е (референция към) потребителски дефиниран тип (не може да се предефинират операциите върху примитивните типове)!  

**Пример:**
```c++
bool operator==(const ComplexNumber& lhs, const ComplexNumber& rhs)
{
	return lhs.getReal() == rhs.getReal() && lhs.getImaginary() == rhs.getImaginary();
}
```

Така предефинираният оператор== за работа с комплексни числа ни позволява да правим следното:
```c++
int main()
{
	ComplexNumber c1(5, 10); // c1 = 5 + 10i
	ComplexNumber c2(5, 10); // c2 = 5 + 10i
	std::cout << (c1 == c2);
}
```

---

Изразите с оператори, приложени върху обекти, автоматично се преобразуват до извиквания на съответните предефиниращи функции или член-функции:
```c++
c1 += cr2 <=> c1.operator+=(c2) 
c1 == c2 <=> operator==(c1, c2)
```

### Предефиниране чрез обикновени или член-функции?
Кога **се налага** да предефинираме оператори чрез обикновени функции?
1. Когато искаме да предефинираме бинарен оператор, чийто **първи аргумент не е обект от нашия клас**.
2. Когато искаме да предефинираме оператор за съществуващ клас **без да променяме дефиницията му**.

**Пример:**  
Как да реализираме cout << complex?
```c++
std::ostream& operator<<(std::ostream& os, const ComplexNumber& complex) 
{
	return os << complex.getReal() << " + i" << complex.getImaginary();
}
```

---

**Проблем:** Ако дефинираме външен за класа оператор, той ще има само външен достъп (няма да вижда private компонентите).

---

# Приятелски функции и приятелски класове

## Приятелски функции

Декларират се със запазената дума **friend** пред прототипа на функцията.  
Приятелските функции **имат достъп до всички компоненти на класа**. Т.е. всички членове на класа са public за тях.  

**Пример:**
```c++
class ComplexNumber
{
private:
    double real;
    double im;

public:
	friend std::ostream& operator<<(std::ostream& os, const ComplexNumber& complex);
    // ...
}

std::ostream& operator<<(std::ostream& os, const ComplexNumber& complex) 
{
	return os << complex.real << " + i" << complex.im <<;
}
```

## Приятелски класове
**friend class <име>**;  
Приятелски клас е клас, чиито член-функции имат право на вътрешен достъп.

**Пример:**
```c++
class ComplexNumber
{
private:
	double real;
	double im;

public:
	friend class ComplexVector;
	// ...
};
```
Декларирайки класа ComplexVector като приятелски за ComplexNumber, той има достъп до всички член-данни/методи на ComplexNumber.

## Задачи

**Задача 1:** Реализирайте клас **ComplexNumber**, който ще се използва за работа с комплексни числа. Предефинирайте оператори със следните функционалности:

- Събиране на комплексни числа.
- Изваждане на комплексни числа.
- Умножение на комплексни числа.
- Деление на комплексни числа.
- Сравняване на комплексни числа.
- Вход от поток/изход към поток.

```c++
int main()
{
	ComplexNumber c1;
	std::cin >> c1;

	ComplexNumber c2;
	std::cin >> c2;

	ComplexNumber result = c2 / c1;
	std::cout << result << std::endl;
}
```

---

**Задача 2:** Реализирайте клас - множество от думи от малки/главни латински букви и цифри. В колекцията ви търсенето трябва да е с **логаритмична сложност**. Предефинирайте:

- Оператори, които събират две колекции (+= и +).
- Оператори, които премахват от думите на лявата колекция тези, които участват и в дясната (-= и -).
- Оператор [], който приема дума и връща дали е в колекцията (за логаритмично време).
- Оператор *=, който добавя дума към колекцията.
- Оператор /=, който премахва дума от колекцията.
- Оператор <<, който отпечатва всички думи в сортиран вид.
- Оператор \>>, който приема думa и я добавя в колекцията.

:bangbang: Копирането на стрингове е бавна операция! Помислете как да организирате данните, за да имате **логаритмично търсене** на дума и при добавяне на нова дума да правите **минимален брой копирания** на стрингове!

```c++
int main()
{
	StringPool dict1;
	((dict1 *= "Ivan") *= "Petur") *= "Alex";
	std::cout << dict1 << std::endl; // {Alex, Ivan, Petur}
	std::cout << dict1["Alex"] << ' ' << dict1["abc"] << std::endl; // 1 0

	StringPool dict2;
	((dict2 *= "Niq") *= "Alex");

	StringPool result1 = dict1 + dict2;
	std::cout << result1 << std::endl; // {Alex, Ivan, Niq, Petur}

	StringPool result2 = dict1 - dict2;
	std::cout << result2 << std::endl; // {Ivan, Petur}

	"NewWord" >> result2;
	result2 /= "NonExistingWord";
	std::cout << result2 << std::endl;  // {Ivan, NewWord, Petur}
	
	"Job" >> result2;
	std::cout << result2 << std::endl;  // {Ivan, Job, NewWord, Petur}
}
```
