#include "ImaginaryNumber.h"
	#include "helper.h"
	
	//partners: rtiwary2, tkarim3
	
	ImaginaryNumber::ImaginaryNumber()
	{
	    imaginary_component = 0;
	    number_type = IMAGINARY;
	    magnitude = 0.0;
	    phase = 0.0;
	}
	
	ImaginaryNumber::ImaginaryNumber(double rval)
	{
	    imaginary_component = rval;
	    number_type = IMAGINARY;
	    magnitude = abs(rval);
	    phase = calculate_phase(0,rval);
	}
	
	ImaginaryNumber::ImaginaryNumber( const ImaginaryNumber& other )
	{
	    imaginary_component = other.get_imaginary_component();
	    number_type = IMAGINARY;
	    magnitude = other.get_magnitude();
	    phase = other.get_phase();
	}

void ImaginaryNumber::set_imaginary_component (double rval)
{
    imaginary_component = rval;
    number_type = IMAGINARY;
    magnitude = abs(rval);
    phase = calculate_phase(0, rval);
}

double ImaginaryNumber::get_imaginary_component() const
{
    return imaginary_component;
}

//Getter function for magnitude
double ImaginaryNumber::get_magnitude() const{
    return magnitude;
}

//Getter function for phase
double ImaginaryNumber::get_phase() const{
    return phase;
}

//Operator Overload
ImaginaryNumber ImaginaryNumber::operator + (const ImaginaryNumber& arg)
{
    return ImaginaryNumber(imaginary_component + arg.get_imaginary_component());
}


ImaginaryNumber ImaginaryNumber::operator - (const ImaginaryNumber& arg)
{
    return ImaginaryNumber(imaginary_component - arg.get_imaginary_component());
}

RealNumber ImaginaryNumber::operator * (const ImaginaryNumber& arg)
{
    return RealNumber(-1 * imaginary_component * arg.get_imaginary_component());
}

RealNumber ImaginaryNumber::operator / (const ImaginaryNumber& arg)
{
    double b = imaginary_component;
    double d = arg.get_imaginary_component();
    return RealNumber(b/d);
}

ComplexNumber ImaginaryNumber::operator + (const RealNumber& arg)
{
    double r_comp = arg.get_real_component();
    double i_comp = imaginary_component;
    return ComplexNumber(r_comp, i_comp);
}

ComplexNumber ImaginaryNumber::operator - (const RealNumber& arg)
{
    double r_comp = -1 * arg.get_real_component();
    double i_comp = imaginary_component;
    return ComplexNumber(r_comp, i_comp);
}

ImaginaryNumber ImaginaryNumber::operator * (const RealNumber& arg)
{
    double r_comp = arg.get_real_component();
    double i_comp = imaginary_component;
    return ImaginaryNumber(r_comp * i_comp);
}

ImaginaryNumber ImaginaryNumber::operator / (const RealNumber& arg)
{
    double r_comp = arg.get_real_component();
    double i_comp = imaginary_component;
    return ImaginaryNumber(i_comp / r_comp);
}

ComplexNumber ImaginaryNumber::operator + (const ComplexNumber& arg)
{
    double r_comp = arg.get_real_component();
    double i_comp = imaginary_component + arg.get_imaginary_component();
    return ComplexNumber(r_comp, i_comp);
}

ComplexNumber ImaginaryNumber::operator - (const ComplexNumber& arg)
{
    double r_comp = -1 * arg.get_real_component();
    double i_comp = imaginary_component - arg.get_imaginary_component();
    return ComplexNumber(r_comp, i_comp);
}

ComplexNumber ImaginaryNumber::operator * (const ComplexNumber& arg)
{
    double r_comp = -1 * imaginary_component * arg.get_imaginary_component();
    double i_comp = imaginary_component * arg.get_real_component();
    return ComplexNumber(r_comp, i_comp);
}

ComplexNumber ImaginaryNumber::operator / (const ComplexNumber& arg)
{
    double r_comp = (imaginary_component * arg.get_imaginary_component()) / (pow(arg.get_real_component(), 2) + pow(arg.get_imaginary_component(), 2));
    double i_comp = (imaginary_component * arg.get_real_component()) / (pow(arg.get_real_component(), 2) + pow(arg.get_imaginary_component(), 2));
    return ComplexNumber(r_comp, i_comp);
}

string ImaginaryNumber::to_String(){
    /* Do not modify */
    stringstream my_output;
    my_output << std::setprecision(3) << imaginary_component << 'i';
    return my_output.str();
}


