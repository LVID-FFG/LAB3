package main

import (
	"fmt"
	"math"
	"math/rand"
	"time"
)

func generate_N_3(k int, control []int) tuple {
	rand.Seed(time.Now().UnixNano())
	f := uint64(1)
	Q := []int{}
	A := []int{}
	var a, q int
	s := f
	var r int
	n := uint64(1)

	for {
		for {
			a = rand.Intn(91)
			q = control[rand.Intn(len(control))]

			if count(Q, q) == 0 {
				s *= uint64(math.Pow(float64(q), float64(a)))

				if math.Pow(2, float64(k/2)) <= float64(s) && float64(s) < math.Pow(2, float64(k/2+1)) {
					f = s
					Q = append(Q, q)
					A = append(A, a)
					break
				} else {
					if len_in_bit(s) < k/2+1 {
						f = s
						Q = append(Q, q)
						A = append(A, a)
					} else {
						s = 2
						f = 2
						Q = []int{}
						A = []int{}
					}
				}
			} else {
				if len(Q) > 45 {
					s = 1
					f = 1
					Q = []int{}
					A = []int{}
				}
			}
		}

		min := int(math.Pow(2, float64(k/2-1)))
		max := int(math.Pow(2, float64(k/2)))
		r = rand.Intn(max-min) + min

		for {
			if r%2 == 0 {
				break
			}
			r = rand.Intn(max-min) + min
		}

		n = uint64(r)*f + 1
		if len_in_bit(n) == k {
			break
		}
	}

	return tuple{n, Q, A}
}

func test_polington(n uint64, Q []int, a []int, t int) int {
	rand.Seed(time.Now().UnixNano())
	a_list := make([]int, 0, t)

	for i := 0; i < t; {
		c := rand.Intn(50000-2) + 2
		if count(a_list, c) == 0 {
			a_list = append(a_list, c)
			i++
		}
	}

	con := 0
	for _, a_val := range a_list {
		if num_exp(uint64(a_val), uint64(n-1), uint64(n)) != 1 {
			return 0
		}
		for _, q := range Q {
			if num_exp(uint64(a_val), uint64((n-1)/uint64(q)), uint64(n)) == 1 {
				break
			}
			con++
		}
		if con == len(Q) {
			return 2
		}
		con = 0
	}
	return 1
}

func polington(k, t int, s ...int) {
	s_val := 2
	if len(s) > 0 {
		s_val = s[0]
	}

	control := resheto_eratosfena()
	list_of_N := make([]tuple, 0, 10)
	list_of_only_N := make([]uint64, 0, 10)

	for i := 0; i < 10; {
		N := generate_N_3(k, control)
		test := test_polington(N.n, N.Q, N.A, t)

		if test != 0 && count_uint64(list_of_only_N, N.n) == 0 && len_in_bit(N.n) == k {
			fmt.Print("По тесту Полингтона - ")
			if test < 2 {
				fmt.Println("скорее всего простое")
			} else {
				fmt.Println("точно простое")
			}
			fmt.Print("По тесту Миллера-Рабина - ")
			fmt.Println(test_millera_rabina(N.n, s_val))
			fmt.Println(N.n, "\n")

			list_of_N = append(list_of_N, N)
			list_of_only_N = append(list_of_only_N, N.n)
			i++
		}
	}
}
