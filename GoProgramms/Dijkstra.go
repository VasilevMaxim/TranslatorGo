package main

import 	"fmt"

const (
	size  = 5
	began = 1
	max = 100000
)

func main() {
	var (
		matrix [size*size]int = [size*size]int{
			0, max, 2, 123, 124,
			max, 0, 34, 44, 56,
			2, 34, 0, 89, max,
			123, 444, 56, 0, max,
			24, max, max, max, 0,
		}
	)
	//matrix3 := ([size]*7)
	//matrix2 :=  [size*size]int{ 0, max, 2, 123, 124,
		/*max, 0, 34, 44, 56,
		2, 34, 0, 89, max,
		123, 444, 56, 0, max,
		24, max, max, max, 0,	}*/
	FindPath(matrix, began - 1)
}

func FindPath(matrix [size*size]int, begin int){
	var(
		visNode [size]bool
		minPath [ size]int
		index, min int = max, max
	)
	for i := 0; i < size; i++ {
		minPath[i] = matrix[begin*size + i]
	}
	minPath[begin] = 0
	for {
		min = max
		index = max
		for j := 0; j < size; j++{
			if !visNode[j] && (minPath[j] < min/* && minPath[j] != max*/){
				min = minPath[j]
				index = j
			}
		}
		//u = index
		if index != max {
			for j := 0; j < size; j++ {
				if (minPath[index]+matrix[index*size+j]) < minPath[j] {
					minPath[j] = minPath[index] + matrix[index*size+j]
				}
			}
			visNode[index] = true
		}
		if index >= max{
			break
		}
	}
	fmt.Println("Кратчайшие пути из вершины ", begin + 1, ": ", minPath)
}
