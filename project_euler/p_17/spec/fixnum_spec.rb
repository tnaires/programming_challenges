require './app/fixnum'

describe Fixnum do
  describe :in_full do
    context 'when greater than 1000' do
      subject { 1001.in_full }

      it { should == 'Out of range' }
    end

    context 'when less than or equals to 1000' do
      specify { 1.in_full.should == 'one' }
      specify { 2.in_full.should == 'two' }
      specify { 3.in_full.should == 'three' }
      specify { 4.in_full.should == 'four' }
      specify { 5.in_full.should == 'five' }
      specify { 6.in_full.should == 'six' }
      specify { 7.in_full.should == 'seven' }
      specify { 8.in_full.should == 'eight' }
      specify { 9.in_full.should == 'nine' }
      specify { 10.in_full.should == 'ten' }
      specify { 11.in_full.should == 'eleven' }
      specify { 12.in_full.should == 'twelve' }
      specify { 13.in_full.should == 'thirteen' }
      specify { 14.in_full.should == 'fourteen' }
      specify { 15.in_full.should == 'fifteen' }
      specify { 16.in_full.should == 'sixteen' }
      specify { 17.in_full.should == 'seventeen' }
      specify { 18.in_full.should == 'eighteen' }
      specify { 19.in_full.should == 'nineteen' }
      specify { 20.in_full.should == 'twenty' }
      specify { 30.in_full.should == 'thirty' }
      specify { 40.in_full.should == 'forty' }
      specify { 50.in_full.should == 'fifty' }
      specify { 60.in_full.should == 'sixty' }
      specify { 70.in_full.should == 'seventy' }
      specify { 80.in_full.should == 'eighty' }
      specify { 90.in_full.should == 'ninety' }

      specify { 21.in_full.should == 'twenty-one' }
      specify { 59.in_full.should == 'fifty-nine' }
      specify { 99.in_full.should == 'ninety-nine' }
      specify { 34.in_full.should == 'thirty-four' }
      specify { 76.in_full.should == 'seventy-six' }
      specify { 44.in_full.should == 'forty-four' }

      specify { 100.in_full.should == 'one hundred' }
      specify { 400.in_full.should == 'four hundred' }
      specify { 235.in_full.should == 'two hundred and thirty-five' }
      specify { 999.in_full.should == 'nine hundred and ninety-nine' }
      specify { 845.in_full.should == 'eight hundred and forty-five' }
      specify { 390.in_full.should == 'three hundred and ninety' }
      specify { 612.in_full.should == 'six hundred and twelve' }
      specify { 777.in_full.should == 'seven hundred and seventy-seven' }

      specify { 1000.in_full.should == 'one thousand' }
    end
  end
end
