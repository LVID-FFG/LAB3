package main

import (
	"fmt"
	"math"
)

func NOD(a, b int) int {
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
	sum := 0.0
	if b == 1 {
		fmt.Println("infinity")
		return
	}

	for n := 0; n < 80000; n++ {
		sum += math.Pow(float64(n), float64(a)) / math.Pow(float64(b), float64(n))
	}

	sumH := uint64(math.Round(sum * math.Pow(10, 9)))
	sumL := uint64(math.Pow(10, 9))

	if sumH%10 == 0 {
		nod := NOD(int(sumH), int(sumL))
		sumH /= uint64(nod)
		sumL /= uint64(nod)
		if (sumL%2 == 0 || sumL%5 == 0 || sumL == 1) && sumL < 10000000 {
			fmt.Printf("%d/%d\n", sumH, sumL)
			return
		}
	}

	nod := NOD(int(sumH), int(sumL))
	sumH /= uint64(nod)
	sumL /= uint64(nod)

	if (sumH/10)%10 == 0 && b == 2 {
		fmt.Println(int(sum))
		return
	}

	for i := 1; i <= 30; i++ {
		pow := math.Pow(2, float64(i))
		if math.Round(sum*pow)*10000-math.Round(sum*pow*10000) == 0 {
			fmt.Printf("%d/%d\n", uint64(sum*pow), uint64(pow))
			return
		}
	}

	for i := 1; i <= 10; i++ {
		pow := math.Pow(5, float64(i))
		if math.Round(sum*pow)*10000-math.Round(sum*pow*10000) == 0 {
			fmt.Printf("%d/%d\n", uint64(sum*pow), uint64(pow))
			return
		}
	}

	fmt.Println("irrational")
}