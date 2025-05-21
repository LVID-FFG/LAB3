package main

import (
	"fmt"
	"math"
	"math/rand"
	"time"
)

// generate_N_1 генерирует простое число по алгоритму ГОСТ (только для t = 9, 10, 13, 14, 21, 22, 25, 26)
func generate_N_1(t int) uint64 {
	q := math.Ceil(float64(t) / 2)
	rand.Seed(time.Now().UnixNano())
	e := rand.Float64()
	N := math.Ceil(math.Pow(2, float64(t-1))/q) + math.Ceil(math.Pow(2, float64(t-1))*e/q)
	if int(N)%2 == 0 {
		N++
	}

	for {
		e = rand.Float64()
		N = math.Ceil(math.Pow(2, float64(t-1))/q) + math.Ceil(math.Pow(2, float64(t-1))*e/q)
		if int(N)%2 == 1 {
			N++
		}

		u := 0
		for {
			p := uint64((float64(N)+float64(u))*q + 1)
			if float64(p) > math.Pow(2, float64(t)) {
				break
			}
			if num_exp(2, uint64(p-1), uint64(p)) == 1 && num_exp(2, uint64(float64(N)+float64(u)), uint64(p)) != 1 {
				return p
			}
			u += 2
		}
	}
}

// gost реализует основной алгоритм ГОСТ
func gost(k int, s int) {

	var N uint64
	listN := make(map[uint64]bool)

	for i := 0; i < 10; {
		N = generate_N_1(k)
		if !listN[N] {
			listN[N] = true
			fmt.Printf("%d по вероятностному тесту - %s\n", N, test_millera_rabina(N, s))
			i++
		}
	}
}
