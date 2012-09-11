require './app/fixnum'

describe Fixnum do
  describe :divisors do
    it { 1.divisors.should == [1]  }
    it { 2.divisors.should == [1, 2] }
    it { 3.divisors.should == [1, 3] }
    it { 10.divisors.should == [1, 2, 5, 10] }
    it { 99.divisors.should == [1, 3, 9, 11, 33, 99] }
    it { 220.divisors.should == [1, 2, 4, 5, 10, 11, 20, 22, 44, 55, 110, 220] }
    it { 284.divisors.should == [1, 2, 4, 71, 142, 284] }
  end

  describe :amicable do
    it { 284.amicable?(220).should be_true }
  end
end
