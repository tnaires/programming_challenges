i = 1

loop do
  n = i * (i + 1) / 2
  sqrt = Math.sqrt(n).floor
  divisors = 2
  (2..sqrt).each {|e| divisors += 2 if n % e == 0 }
  divisors -= 1 if sqrt * sqrt == n

  if divisors > 500
    puts n
    break
  end

  i += 1
end
