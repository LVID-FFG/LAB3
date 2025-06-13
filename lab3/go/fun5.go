package main

import (
	"fmt"
)

func fun5(T, T_s, r float64, t_max, t_step int) {
	// температура кофе, окр. температура, коэф. остывания, макс. время, шаг измерения времени.
	fmt.Println("Время Температура кофе")
	tempCofe := []struct {
		time int
		temp float64
	}{{0, T}}

	var dT float64
	for i := 1; i <= t_max; i++ {
		dT = -1 * r * (T - T_s) // вычисляем dT/dt
		T += dT
		tempCofe = append(tempCofe, struct {
			time int
			temp float64
		}{i, T})
	}

	for _, temp := range tempCofe {
		if temp.time%t_step == 0 {
			fmt.Printf("%5d %.1f\n", temp.time, temp.temp)
		}
	}
}
