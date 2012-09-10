class Fixnum
  def in_full
    return 'Out of range' if self > 1000
    return 'one thousand' if self == 1000

    numbers_in_full = Fixnum.numbers_in_full
    return numbers_in_full[self] if numbers_in_full.has_key?(self)

    if self >= 100
      hundred_count = self / 100
      factor = hundred_count * 100
      remaining = self - factor
      result = "#{hundred_count.in_full} hundred"
      result += " and #{remaining.in_full}" if remaining > 0
      return result
    end

    if self > 20
      factor = (self / 10) * 10
      last_digit = self - factor
      return "#{numbers_in_full[factor]}-#{last_digit.in_full}"
    end    
  end

  class << self
    def numbers_in_full
      {
        1 => 'one', 2 => 'two', 3 => 'three', 4 => 'four', 5 => 'five',
        6 => 'six', 7 => 'seven', 8 => 'eight', 9 => 'nine', 10 => 'ten',
        11 => 'eleven', 12 => 'twelve', 13 => 'thirteen', 14 => 'fourteen',
        15 => 'fifteen', 16 => 'sixteen', 17 => 'seventeen',
        18 => 'eighteen', 19 => 'nineteen', 20 => 'twenty', 30 => 'thirty',
        40 => 'forty', 50 => 'fifty', 60 => 'sixty', 70 => 'seventy',
        80 => 'eighty', 90 => 'ninety'
      }
    end
  end
end
