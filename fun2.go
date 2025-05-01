package main

import (
	"fmt"
	"math"
	"math/rand"
	"time"
)

type NumberInfo struct {
	N uint64
	Q []int
	A []int
}

func lenInBit(a uint64) int {
	result := 0
	for a != 0 {
		result++
		a /= 2
	}
	return result
}

func reshetoEratosfena() []int {
	result := []int{1}
	for i := 2; i < 500; i++ {
		result = append(result, i)
	}

	for x := 2; x < 500; x++ {
		for j := 0; j < len(result); j++ {
			if result[j]%x == 0 && result[j] != x {
				result[j] = 0
			}
		}
	}

	var filtered []int
	for _, num := range result {
		if num != 0 {
			filtered = append(filtered, num)
		}
	}
	return filtered
}

func generateN(k int, control []int) NumberInfo {
	rand.Seed(time.Now().UnixNano())
	m := uint64(2)
	Q := []int{2}
	A := []int{1}
	var a, q int
	s := m

	for {
		a = rand.Intn(50) + 1
		q = control[rand.Intn(len(control))]
		if !contains(Q, q) {
			s *= uint64(math.Pow(float64(q), float64(a)))
			if math.Pow(2, float64(k-1)) <= float64(s) && float64(s) <= math.Pow(2, float64(k)) {
				m = s
				Q = append(Q, q)
				A = append(A, a)
				break
			} else {
				if lenInBit(s) < k {
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
	return NumberInfo{N: n, Q: Q, A: A}
}

func contains(slice []int, item int) bool {
	for _, v := range slice {
		if v == item {
			return true
		}
	}
	return false
}

func numExp(n, exp, p uint64) uint64 {
	if exp == 0 {
		return 1
	}
	z := numExp(n%p, exp/2, p) % p
	if exp%2 == 0 {
		return (z * z) % p
	}
	return ((n % p) * ((z * z) % p)) % p
}

func testMilleraRabina(n uint64, k int) string {
	s := 0
	t := n - 1
	rand.Seed(time.Now().UnixNano())

	for t%2 == 0 {
		s++
		t /= 2
	}

	for i := 0; i < k; i++ {
		x := numExp(uint64(rand.Intn(10000000)+2), t, n)
		if x == 1 || x == n-1 {
			continue
		}
		for j := 0; j < s-1; j++ {
			x = numExp(x, 2, n)
			if x == 1 {
				return "составное"
			}
			if x == n-1 {
				break
			}
		}
		if x != n-1 {
			return "составное"
		}
	}
	return "вероятно простое"
}

func testMillera(num NumberInfo, t int) int {
	rand.Seed(time.Now().UnixNano())
	tList := make([]int, 0, t)

	for len(tList) < t {
		c := rand.Intn(100) + 1
		if !contains(tList, c) {
			tList = append(tList, c)
		}
	}

	for _, i := range tList {
		if numExp(uint64(i), num.N-1, num.N) != 1 {
			return 0
		}
	}

	c := 0
	for _, q := range num.Q {
		for _, i := range tList {
			if numExp(uint64(i), (num.N-1)/uint64(q), num.N) == 1 {
				c++
			} else {
				break
			}
		}
	}

	if c < len(num.Q) {
		return 1
	}
	return 2
}

func fun2(k, t, s int) {
	control := reshetoEratosfena()
	listOfN := make([]NumberInfo, 0, 10)
	listOfOnlyN := make([]uint64, 0, 10)

	for i := 0; i < 10; {
		N := generateN(k, control)
		test := testMillera(N, t)
		if test != 0 && !containsUint64(listOfOnlyN, N.N) {
			fmt.Print("По тесту Миллера - ")
			if test < 2 {
				fmt.Println("скорее всего простое")
			} else {
				fmt.Println("точно простое")
			}
			fmt.Print("По тесту Миллера-Рабина - ")
			fmt.Println(testMilleraRabina(N.N, s))
			fmt.Println(N)
			listOfN = append(listOfN, N)
			listOfOnlyN = append(listOfOnlyN, N.N)
			i++
		}
	}
}

func containsUint64(slice []uint64, item uint64) bool {
	for _, v := range slice {
		if v == item {
			return true
		}
	}
	return false
}

func (n NumberInfo) String() string {
	return fmt.Sprintf("%d\n%v\n%v\n", n.N, n.Q, n.A)
}
