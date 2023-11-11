/*
    Following is AOC 2022 day 6 problem.
*/

package main

import (
    "fmt"
    "os"
    "time"
    "github.com/emirpasic/gods/sets/hashset"
)


func Simple(input string) {
    for i := 0; i < len(input)-14; i++ {
        set := hashset.New()
        for _, v := range input[i:i+14]{
            set.Add(v)
        }
        if len(set.Values()) == 14 {
            break
        }
    }
}

func BitBetter(input string) {
    for i := 0; i < len(input)-14; i++ {
        set := hashset.New()
        for _, v := range input[i:i+14] {
            if set.Contains(v) {
                break
            }
            set.Add(v)
        }
        if len(set.Values()) == 14 {
            break
        }
    }
}

func Timer (name string, a func()){
    start := time.Now()
    a()
    fmt.Printf("%s took %v\n", name, time.Since(start))
}


func main() { 
    input, _ := os.ReadFile("input");
    
    Timer("Simple", func() {
        Simple(string(input))
    })

    Timer("BitBetter", func() {
        BitBetter(string(input))
    })
}
