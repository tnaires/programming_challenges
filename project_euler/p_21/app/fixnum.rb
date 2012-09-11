class Fixnum
  def divisors
    result = []

    1.upto(self / 2) do |n|
      result << n if self % n == 0
    end

    result << self
  end

  def amicable?(n)
    self_divisors = self.divisors
    self_divisors.pop

    n_divisors = n.divisors
    n_divisors.pop

    self_divisors.inject(:+) == n &&  n_divisors.inject(:+) == self
  end 
end
