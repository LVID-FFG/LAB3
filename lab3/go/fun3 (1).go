package main

import (
	"fmt"
	"math"
)

// Функция для нахождения наибольшего общего делителя
func NOD(a, b uint64) uint64 {
	if a%b == 0 {
		return b
	}
	if b%a == 0 {
		return a
	}
	if a > b {
		return NOD(a%b, b)
	}
	return NOD(a, b%a)
}

func fun3(a, b int) {
	if b == 1 {
		fmt.Println("infinity")
		return
	}

	// Проверка на иррациональность
	if (b-1)%5 != 0 && (b-1)%2 != 0 && b-1 != 1 || b-1 == 6 {
		fmt.Println("irrational")
		return
	}

	var numH, numL uint64

	switch a {
	case 1:
		numH = uint64(b)
		numL = uint64(math.Pow(float64(b-1), 2))
	case 2:
		numH = uint64(b) * uint64(b+1)
		numL = uint64(math.Pow(float64(b-1), 3))
	case 3:
		numH = uint64(b) * (uint64(math.Pow(float64(b), 2)) + 4*uint64(b) + 1)
		numL = uint64(math.Pow(float64(b-1), 4))
	case 4:
		numH = uint64(b) * (uint64(math.Pow(float64(b), 3)) + 11*uint64(math.Pow(float64(b), 2)) + 11*uint64(b) + 1)
		numL = uint64(math.Pow(float64(b-1), 5))
	case 5:
		numH = uint64(b) * (uint64(math.Pow(float64(b), 4)) + 26*uint64(math.Pow(float64(b), 3)) + 66*uint64(math.Pow(float64(b), 2)) + 26*uint64(b) + 1)
		numL = uint64(math.Pow(float64(b-1), 6))
	case 6:
		numH = uint64(b) * (uint64(math.Pow(float64(b), 5)) + 57*uint64(math.Pow(float64(b), 4)) + 302*uint64(math.Pow(float64(b), 3)) + 302*uint64(math.Pow(float64(b), 2)) + 57*uint64(b) + 1)
		numL = uint64(math.Pow(float64(b-1), 7))
	case 7:
		numH = uint64(b) * (uint64(math.Pow(float64(b), 6)) + 120*uint64(math.Pow(float64(b), 5)) + 1191*uint64(math.Pow(float64(b), 4)) +
			2416*uint64(math.Pow(float64(b), 3)) + 1191*uint64(math.Pow(float64(b), 2)) + 120*uint64(b) + 1)
		numL = uint64(math.Pow(float64(b-1), 8))
	case 8:
		numH = uint64(b) * (uint64(math.Pow(float64(b), 7)) + 247*uint64(math.Pow(float64(b), 6)) + 4293*uint64(math.Pow(float64(b), 5)) +
			15619*uint64(math.Pow(float64(b), 4)) + 15619*uint64(math.Pow(float64(b), 3)) + 4293*uint64(math.Pow(float64(b), 2)) + 247*uint64(b) + 1)
		numL = uint64(math.Pow(float64(b-1), 9))
	case 9:
		numH = uint64(b) * (uint64(math.Pow(float64(b), 8)) + 502*uint64(math.Pow(float64(b), 7)) + 14608*uint64(math.Pow(float64(b), 6)) +
			88234*uint64(math.Pow(float64(b), 5)) + 156190*uint64(math.Pow(float64(b), 4)) + 88234*uint64(math.Pow(float64(b), 3)) +
			14608*uint64(math.Pow(float64(b), 2)) + 502*uint64(b) + 1)
		numL = uint64(math.Pow(float64(b-1), 10))
	case 10:
		numH = uint64(b) * (uint64(math.Pow(float64(b), 9)) + 1013*uint64(math.Pow(float64(b), 8)) + 47840*uint64(math.Pow(float64(b), 7)) +
			455192*uint64(math.Pow(float64(b), 6)) + 1310354*uint64(math.Pow(float64(b), 5)) + 1310354*uint64(math.Pow(float64(b), 4)) +
			455192*uint64(math.Pow(float64(b), 3)) + 47840*uint64(math.Pow(float64(b), 2)) + 1013*uint64(b) + 1)
		numL = uint64(math.Pow(float64(b-1), 11))
	default:
		return
	}

	nod := NOD(numH, numL)
	fmt.Printf("%d/%d\n", numH/nod, numL/nod)
}
