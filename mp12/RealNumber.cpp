#include "RealNumber.h"
	#include "helper.h"
	
	//partners: rtiwary2, tkarim3
	
	RealNumber::RealNumber()
	{
	    real_component = 0;
	    number_type = REAL;
	    magnitude = 0.0;
	    phase = 0.0;
	}

RealNumber::RealNumber(double rval)
{
    number_type = REAL;
    real_component = rval;
    magnitude = abs(rval);
    phase = calculate_phase(rval,0);
}

RealNumber::RealNumber( const RealNumber& other )
{
    real_component = other.get_real_component();
    number_type = REAL;
    magnitude = other.get_magnitude();
    phase = other.get_phase();
}

void RealNumber::set_real_component (double rval)
{
    real_component = rval;
    number_type = REAL;
    magnitude = abs(rval);
    phase = calculate_phase(rval,0);
}

double RealNumber::get_real_component() const
{
    return real_component;
}

double RealNumber::get_magnitude() const{
    return magnitude;
}

double RealNumber::get_phase() const{
    return phase;
}

RealNumber RealNumber::operator + (const RealNumber& arg)
{
    return RealNumber(real_component + arg.get_real_component());
}

RealNumber RealNumber::operator - (const RealNumber& arg)
{
    return RealNumber(real_component - arg.get_real_component());
}

RealNumber RealNumber::operator * (const RealNumber& arg)
{
    return RealNumber(real_component * arg.get_real_component());
}

RealNumber RealNumber::operator / (const RealNumber& arg)
{
    return RealNumber(real_component / arg.get_real_component());
}

ComplexNumber RealNumber::operator + (const ImaginaryNumber& arg){
        double r_comp = real_component;
        double i_comp = arg.get_imaginary_component();
       return ComplexNumber(r_comp, i_comp);
}

ComplexNumber RealNumber::operator - (const ImaginaryNumber& arg){
        double r_comp = real_component;
        double i_comp = -1 * arg.get_imaginary_component();
       return ComplexNumber(r_comp, i_comp);
}

ImaginaryNumber RealNumber::operator * (const ImaginaryNumber& arg){
        double r_comp = real_component;
        double i_comp = arg.get_imaginary_component();
       return ImaginaryNumber(r_comp * i_comp);
}

ImaginaryNumber RealNumber::operator / (const ImaginaryNumber& arg){
        double r_comp = real_component;
        double i_comp = arg.get_imaginary_component();
       return ImaginaryNumber(-1 * (r_comp / i_comp));
}

ComplexNumber RealNumber::operator + (const ComplexNumber& arg){
        double r_comp = real_component + arg.get_real_component();
        double i_comp = arg.get_imaginary_component();
       return ComplexNumber(r_comp, i_comp);
}

ComplexNumber RealNumber::operator - (const ComplexNumber& arg){
        double r_comp = real_component - arg.get_real_component();
        double i_comp = -1 * arg.get_imaginary_component();
       return ComplexNumber(r_comp, i_comp);
}

ComplexNumber RealNumber::operator * (const ComplexNumber& arg){
        double r_comp = real_component * arg.get_real_component();
        double i_comp = real_component * arg.get_imaginary_component();
       return ComplexNumber(r_comp, i_comp);
}

ComplexNumber RealNumber::operator / (const ComplexNumber& arg){
        double r_comp = (real_component * arg.get_real_component()) / (pow(arg.get_real_component(), 2) + pow(arg.get_imaginary_component(), 2));
        double i_comp = (-1 * (real_component * arg.get_imaginary_component())) / (pow(arg.get_real_component(), 2) + pow(arg.get_imaginary_component(), 2));
       return ComplexNumber(r_comp, i_comp);
}

string RealNumber::to_String(){
    /* Do not modify */
    stringstream my_output;
    my_output << std::setprecision(3) << real_component;
    return my_output.str();
}


