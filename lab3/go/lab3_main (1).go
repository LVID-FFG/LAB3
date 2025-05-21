package main

import (
	"fmt"
	"os"
)

func main() {
	var x int

	for {
		fmt.Println("Выберете задание, для выхода введите 0")
		fmt.Println("График - 1")
		fmt.Println("Генераторы простых чисел - 2")
		fmt.Println("Ряд - 3")
		fmt.Println("Игра - 4")
		fmt.Println("Кофе - 5")

		fmt.Scan(&x)

		switch x {
		case 1:
			Fun1()
		case 2:
			Fun2()
		case 3:
			Fun3()
		case 4:
			Fun4()
		case 5:
			Fun5()
		default:
			fmt.Println("Завершение работы")
			os.Exit(0)
		}
		fmt.Println()
	}
}

func Fun1() {
	var x_n, x_k, stp float64
	fmt.Println("Введите начало отрезка")
	fmt.Scan(&x_n)
	fmt.Println("Введите конец отрезка")
	fmt.Scan(&x_k)
	fmt.Println("Введите шаг")
	fmt.Scan(&stp)
	fun1(x_n, x_k, stp)
}

func Fun2() {
	var choice, bit, t, s int
	fmt.Println("Выберете генератор простых чисел")
	fmt.Println("1 - Миллера, 2 - Полингтона, 3 - ГОСТ")
	fmt.Scan(&choice)
	switch choice {
	case 1:
		fmt.Println("Введите размер числа в битах (не более 32)")
		fmt.Scan(&bit)
		fmt.Println("Введите параметр надёжности теста Миллера")
		fmt.Scan(&t)
		fmt.Println("Введите количество раундов теста Миллера-Рабина")
		fmt.Scan(&s)
		miller(bit, t, s)
	case 2:
		fmt.Println("Введите размер числа в битах (не более 32)")
		fmt.Scan(&bit)
		fmt.Println("Введите параметр надёжности теста Полингтона")
		fmt.Scan(&t)
		fmt.Println("Введите количество раундов теста Миллера-Рабина")
		fmt.Scan(&s)
		polington(bit, t, s)
	case 3:
		fmt.Println("Введите размер числа в битах (только для 9, 10, 13, 14, 21, 22, 25, 26)")
		fmt.Scan(&bit)
		fmt.Println("Введите количество раундов теста Миллера-Рабина")
		fmt.Scan(&s)
		gost(bit, s)
	}
}

func Fun3() {
	var a, b int
	fmt.Println("Введите a, (n^a/b^n)")
	fmt.Scan(&a)
	fmt.Println("Введите b")
	fmt.Scan(&b)
	fun3(a, b)
}

func Fun4() {
	var m int
	fmt.Println("Введите максимальную длину хода (от 4 до 100)")
	fmt.Scan(&m)
	fun4(m)
	os.Exit(0)
}

func Fun5() {
	var T, T_s, r float64
	var t_max, t_st int
	fmt.Println("Введите начальную температуру кофе")
	fmt.Scan(&T)
	fmt.Println("Введите температуру окружающей среды")
	fmt.Scan(&T_s)
	fmt.Println("Введите коэффициент остывания")
	fmt.Scan(&r)
	fmt.Println("Введите время наблюдения")
	fmt.Scan(&t_max)
	fmt.Println("Введите шаг измерения температуры")
	fmt.Scan(&t_st)
	fun5(T, T_s, r, t_max, t_st)
}
