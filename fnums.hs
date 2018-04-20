{-
    Convert functors to numbers and see how they behave 
-}

check :: [Int] -> [Int] -> [Int] -> Bool
check x y z = 
    all isOk $ zip x y
    where isOk (px, py) = z !! (px * 2 + py) == 1

checkNum :: Int -> Int -> Int -> Bool
checkNum x y z =
    check (conv x) (conv y) (conv z)
    where conv n = numToArr 2 [0, 0, 0, 0] n 

checkFunc :: [Int] -> [(Int, Int, Bool)]
checkFunc fu = 
    let
        funum = arrToNum 2 0 0 fu
        poss = generatePoss 1 0 [[0, 0, 0, 0, 0, 0, 0, 0]]
    in
    map (\(a, b) -> (a, b, checkNum a b funum)) . 
    map (\(a, b) -> (arrToNum 2 0 0 a, arrToNum 2 0 0 b)) . 
    map (\arr -> (take 4 arr, drop 4 arr)) 
    $ poss

    -- not bounded, does not check for errors
succArr :: (Enum a, Eq a) => a -> a -> [a] -> [a] 
succArr m o [] = [o]
succArr m o (x : xs) 
    | x == m    = o : (succArr m o xs)
    | otherwise = (succ x) : xs

generatePoss :: (Enum a, Eq a) => a -> a -> [[a]] -> [[a]] 
generatePoss m o initial 
    | all (== m) (head initial) = initial
    | otherwise                 = generatePoss m o ((succArr m o (head initial)) : initial)

arrToNum :: Int -> Int -> Int -> [Int] -> Int
arrToNum base acc pow []  = acc
arrToNum base acc pow arr = arrToNum base (acc + ((last arr) * (base ^ pow))) (succ pow) (init arr)

numToArr :: Int -> [Int] -> Int -> [Int]
numToArr base acc 0 = acc
numToArr base acc x = numToArr base ((x `mod` base) : acc) (x `quot` base)

