package main

import (
	"fmt"
	"os"
	"strconv"
)

func main() {
	for {
		fmt.Println("Выберете задание, для выхода введите 0")
		fmt.Println("График - 1")
		fmt.Println("Генератор простых чисел - 2")
		fmt.Println("Ряд - 3")
		fmt.Println("Игра - 4")
		fmt.Println("Кофе - 5")

		var input string
		fmt.Scan(&input)
		x, err := strconv.Atoi(input)
		if err != nil {
			fmt.Println("Ошибка ввода")
			os.Exit(0)
		}

		switch x {
		case 1:
			var x_n, x_k, stp float64
			fmt.Println("Введите начало отрезка")
			if _, err := fmt.Scan(&x_n); err != nil {
				fmt.Println("Ошибка ввода")
				os.Exit(0)
			}

			fmt.Println("Введите конец отрезка")
			if _, err := fmt.Scan(&x_k); err != nil || x_k < x_n {
				fmt.Println("Ошибка ввода")
				os.Exit(0)
			}

			fmt.Println("Введите шаг")
			if _, err := fmt.Scan(&stp); err != nil || stp <= 0 {
				fmt.Println("Ошибка ввода")
				os.Exit(0)
			}

			fun1(x_n, x_k, stp)
		case 2:
			var bit, t, s int
			fmt.Println("Введите длину числа в битах (от 8 до 32)")
			if _, err := fmt.Scan(&bit); err != nil || bit < 8 || bit > 32 {
				fmt.Println("Ошибка ввода")
				os.Exit(0)
			}

			fmt.Println("Введите параметр надёжности теста Миллера")
			if _, err := fmt.Scan(&t); err != nil || t <= 0 {
				fmt.Println("Ошибка ввода")
				os.Exit(0)
			}

			fmt.Println("Введите количество раундов теста Миллера-Рабина")
			if _, err := fmt.Scan(&s); err != nil || s <= 0 {
				fmt.Println("Ошибка ввода")
				os.Exit(0)
			}

			fun2(bit, t, s)
		case 3:
			var a, b int
			fmt.Println("Введите a, (n^a/b^n)")
			if _, err := fmt.Scan(&a); err != nil || a < 1 || a > 10 {
				fmt.Println("Ошибка ввода")
				os.Exit(0)
			}

			fmt.Println("Введите b")
			if _, err := fmt.Scan(&b); err != nil || b < 1 || b > 10 {
				fmt.Println("Ошибка ввода")
				os.Exit(0)
			}

			fun3(a, b)
		case 4:
			var m int
			fmt.Println("Введите максимальную длину хода (от 4 до 100)")
			if _, err := fmt.Scan(&m); err != nil || m < 4 || m > 100 {
				fmt.Println("Ошибка ввода")
				os.Exit(0)
			}

			fun4(m)
			os.Exit(0)
		case 5:
			var T, T_s, r float64
			var t_max, t_st int

			fmt.Println("Введите начальную температуру кофе")
			if _, err := fmt.Scan(&T); err != nil {
				fmt.Println("Ошибка ввода")
				os.Exit(0)
			}

			fmt.Println("Введите температуру окружающей среды")
			if _, err := fmt.Scan(&T_s); err != nil || T_s > T {
				fmt.Println("Ошибка ввода")
				os.Exit(0)
			}

			fmt.Println("Введите коэффициент остывания")
			if _, err := fmt.Scan(&r); err != nil || r <= 0 || r >= 1 {
				fmt.Println("Ошибка ввода")
				os.Exit(0)
			}

			fmt.Println("Введите время наблюдения")
			if _, err := fmt.Scan(&t_max); err != nil || t_max <= 0 {
				fmt.Println("Ошибка ввода")
				os.Exit(0)
			}

			fmt.Println("Введите шаг измерения температуры")
			if _, err := fmt.Scan(&t_st); err != nil || t_st <= 0 {
				fmt.Println("Ошибка ввода")
				os.Exit(0)
			}

			fun5(T, T_s, r, t_max, t_st)
		default:
			os.Exit(0)
		}
	}
}
