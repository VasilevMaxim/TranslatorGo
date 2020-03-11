 
func solveMinor3x3 (matrix [3*3]float64, column int, row int) float64 {
	if (column + row)%2 != 0{
		temp = -1*temp
	}
	var (
		temp float64 = 0
		tempMatrix [2*2]float64
	)
	var itemp, jtemp int = 0, 0
	for i := 0; i < size; i++{
		if i != column{
			for j := 0; j < size; j++{
					if j != row{
						tempMatrix[itemp*(2)+jtemp] = matrix[i*(3)+j]
						jtemp++
				}
			}
			jtemp = 0
			itemp++
		}
	}
	for i := 0; i < size - 1; i++{
			temp = temp + solveMinor2x2(tempMatrix)
	}

	return temp*matrix[column*(size) + row]
}


    func testFunc2(x [4]int, y float64)float64 {
		g := 1.9823 * 23213.424

		var numbers [5]int
		var numbers [1 + 5 * g + 6 / y]int = [5]int{1,2}
		var numbers [5]int = [5]int{1,2,3,4,5}
		var numbers [1 + 5 * g + 6 / y]float64 = [5]int{1,2}
		numbers := [5]int{1,2,3,4,5}
	   x := ++a + b--
	   var numbers [5]int

   
	   for i := 1; i < 10; --i{
        
			for j := 1; j < 10; j++{
            
				for k := 1; k < 10; k--{
            
					if a > b {
						if b > c{
								if c < d{
										b = a;
								}
						}
					}
				}
			}
        
	   }




	   var numbers [5]int
	   var numbers [5]int = [5]int{1,2,3,4,5}

	   var hello int


	   var name, age, sss = 5, 27, 9000

		a := 8
		b := 7

		var (








			name = 2
			age = 27
		)

	
		var hello int = 1 + 5 * g + 6 / y
	


		for i < 3 {
			i = i + 1
		}

		for {
			break
		}
    
	}


	
    