class Fixnum
  def divisors
    self.proper_divisors << self
  end

  def proper_divisors
    result = []

    1.upto(self / 2) do |n|
      result << n if self % n == 0
    end

    result
  end

  def amicable?(n)
    self != n &&
    self.proper_divisors.inject(:+) == n &&
    n.proper_divisors.inject(:+) == self
  end 
end
