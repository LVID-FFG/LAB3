package main

import (
	"fmt"
	"math/rand"
	"time"
)

// lenInBit возвращает длину числа в битах
func len_in_bit(a uint64) int {
	result := 0
	for a != 0 {
		result++
		a /= 2
	}
	return result
}

// reshetoEratosfena реализует решето Эратосфена
func resheto_eratosfena() []int {
	result := []int{1}

	// Заполняем слайс числами от 2 до 499
	for i := 2; i < 500; i++ {
		result = append(result, i)
	}

	// Просеиваем составные числа
	for x := 2; x < 500; x++ {
		for j := 0; j < len(result); j++ {
			if result[j]%x == 0 && result[j] != x {
				result[j] = 0
			}
		}
	}

	// Удаляем нули из слайса
	filtered := result[:0]
	for _, num := range result {
		if num != 0 {
			filtered = append(filtered, num)
		}
	}

	return filtered
}

// модульное возведение в степень
func num_exp(a, n, p uint64) uint64 {
	if a < 1 || n < 1 || p < 1 {
		fmt.Println("Ошибка, числа не должны быть отрицательными")
		return 0
	}

	// Находим двоичное представление степени
	nBin := []int{}
	for n != 0 {
		nBin = append(nBin, int(n%2))
		n /= 2
	}

	result := uint64(1)
	for _, bit := range nBin {
		if bit == 1 {
			result = (result * a) % p
		}
		a = (a * a) % p
	}
	return result
}

// testMillerRabin реализует тест Миллера-Рабина
func test_millera_rabina(n uint64, k int) string {
	if n < 2 {
		return "составное"
	}
	if n == 2 || n == 3 {
		return "вероятно простое"
	}
	if n%2 == 0 {
		return "составное"
	}

	// Инициализация генератора случайных чисел
	rand.Seed(time.Now().UnixNano())

	// Находим s и t: n-1 = 2^s * t
	s := 0
	t := n - 1
	for t%2 == 0 {
		s++
		t /= 2
	}

	// Параметры для генерации случайного числа
	min := uint64(2)
	max := uint64(999999)
	if len_in_bit(n) < 32 {
		max = n - 2
	}

	for i := 0; i < k; i++ {
		// Генерируем случайное число в диапазоне [min, max]
		a := min + uint64(rand.Int63n(int64(max-min+1)))

		x := num_exp(a, t, n)
		if x == 1 || x == n-1 {
			continue
		}

		composite := true
		for j := 0; j < s-1; j++ {
			x = num_exp(x, 2, n)
			if x == 1 {
				return "составное"
			}
			if x == n-1 {
				composite = false
				break
			}
		}

		if composite {
			return "составное"
		}
	}

	return "вероятно простое"
}
