package main

import (
	"fmt"
	"math"
	"math/rand"
	"time"
)

type tuple struct {
	n uint64
	Q []int
	A []int
}

func generate_N_2(k int, control []int) tuple {
	rand.Seed(time.Now().UnixNano())
	m := uint64(2)
	Q := []int{2}
	A := []int{1}
	var a, q int
	s := m

	for {
		a = rand.Intn(50) + 1
		q = control[rand.Intn(len(control))]

		if count(Q, q) == 0 {
			s *= uint64(math.Pow(float64(q), float64(a)))

			if math.Pow(2, float64(k-1)) <= float64(s) && float64(s) < math.Pow(2, float64(k)) {
				m = s
				Q = append(Q, q)
				A = append(A, a)
				break
			} else {
				if len_in_bit(s) < k {
					m = s
					Q = append(Q, q)
					A = append(A, a)
				} else {
					s = 2
					m = 2
					Q = []int{2}
					A = []int{1}
				}
			}
		} else {
			if len(Q) > 45 {
				s = 2
				m = 2
				Q = []int{2}
				A = []int{1}
			}
		}
	}

	n := m + 1
	return tuple{n, Q, A}
}

func test_millera(num tuple, t int) int {
	rand.Seed(time.Now().UnixNano())
	t_list := make([]int, 0, t)

	for i := 0; i < t; {
		c := rand.Intn(100) + 1
		if count(t_list, c) == 0 {
			t_list = append(t_list, c)
			i++
		}
	}

	for _, i := range t_list {
		if num_exp(uint64(i), uint64(num.n-1), uint64(num.n)) != 1 {
			return 0
		}
	}

	q_list := num.Q
	c := 0
	for _, q := range q_list {
		for _, i := range t_list {
			if num_exp(uint64(i), uint64((num.n-1)/uint64(q)), uint64(num.n)) == 1 {
				c++
			} else {
				break
			}
		}
	}

	if c < len(q_list) {
		return 1
	}
	return 2
}

func miller(k, t, s int) {
	control := resheto_eratosfena()
	list_of_N := make([]tuple, 0, 10)
	list_of_only_N := make([]uint64, 0, 10)

	for i := 0; i < 10; {
		N := generate_N_2(k, control)
		test := test_millera(N, t)

		if test != 0 && count_uint64(list_of_only_N, N.n) == 0 {
			fmt.Print("По тесту Миллера - ")
			if test < 2 {
				fmt.Println("скорее всего простое")
			} else {
				fmt.Println("точно простое")
			}
			fmt.Print("По тесту Миллера-Рабина - ")
			fmt.Println(test_millera_rabina(N.n, s))
			fmt.Println(N.n)

			list_of_N = append(list_of_N, N)
			list_of_only_N = append(list_of_only_N, N.n)
			i++
		}
	}
}

// Вспомогательные функции

func count(slice []int, val int) int {
	c := 0
	for _, v := range slice {
		if v == val {
			c++
		}
	}
	return c
}

func count_uint64(slice []uint64, val uint64) int {
	c := 0
	for _, v := range slice {
		if v == val {
			c++
		}
	}
	return c
}
