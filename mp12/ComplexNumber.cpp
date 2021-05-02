#include "ComplexNumber.h"
	#include "helper.h"
	
	//partners: shreyav3, tkarim3
	
	ComplexNumber::ComplexNumber()
	{
	    real_component = 0;
	    imaginary_component = 0;
	    number_type = COMPLEX;
	    magnitude = 0.0;
	    phase = 0.0;
	}
	
	ComplexNumber::ComplexNumber(double rval_real_component, double rval_imaginary_component)
	{
	    real_component = rval_real_component;
	    imaginary_component = rval_imaginary_component;
	    number_type = COMPLEX;
	    magnitude = sqrt(pow(real_component, 2) + pow(imaginary_component, 2));
	    phase = calculate_phase(real_component, imaginary_component);
	}
	
	ComplexNumber::ComplexNumber( const ComplexNumber& other )
	{
	    real_component = other.get_real_component();
	    imaginary_component = other.get_imaginary_component();
	    number_type = COMPLEX;
	    magnitude = other.get_magnitude();
	    phase = other.get_phase();
	}
void ComplexNumber::set_real_component (double rval)
{
    real_component = rval;
    number_type = COMPLEX;
    magnitude = sqrt(pow(real_component, 2) + pow(imaginary_component, 2));
    phase = calculate_phase(real_component, imaginary_component);
}

double ComplexNumber::get_real_component() const
{
    return real_component;
}

void ComplexNumber::set_imaginary_component (double rval)
{
    imaginary_component = rval;
    number_type = COMPLEX;
    magnitude = sqrt(pow(real_component, 2) + pow(imaginary_component, 2));
    phase = calculate_phase(real_component, imaginary_component);
}

double ComplexNumber::get_imaginary_component() const
{
    return imaginary_component;
}

double ComplexNumber::get_magnitude() const{
    return magnitude;
}

double ComplexNumber::get_phase() const{
    return phase;
}

ComplexNumber ComplexNumber::operator + (const ComplexNumber& arg)
{
    double a = real_component;
    double b = imaginary_component;
    double c = arg.get_real_component();
    double d = arg.get_imaginary_component();
    return ComplexNumber((a+c), (b+d));
}

ComplexNumber ComplexNumber::operator - (const ComplexNumber& arg)
{
    double a = real_component;
    double b = imaginary_component;
    double c = arg.get_real_component();
    double d = arg.get_imaginary_component();
    return ComplexNumber((a-c), (b-d));
}

ComplexNumber ComplexNumber::operator * (const ComplexNumber& arg)
{
    double a = real_component;
    double b = imaginary_component;
    double c = arg.get_real_component();
    double d = arg.get_imaginary_component();
    return ComplexNumber(((a*c)-(b*d)), ((a*d)+(b*c)));
}

ComplexNumber ComplexNumber::operator / (const ComplexNumber& arg)
{
    double a = real_component;
    double b = imaginary_component;
    double c = arg.get_real_component();
    double d = arg.get_imaginary_component();
    return ComplexNumber(((a*c)+(b*d))/(pow(c,2) + pow(d,2)), ((b*c)-(a*d))/(pow(c,2) + pow(d,2)));
}

ComplexNumber ComplexNumber::operator + (const RealNumber& arg)
{
    double a = real_component;
    double b = imaginary_component;
    double c = arg.get_real_component();
    return ComplexNumber((a+c), b);
}

ComplexNumber ComplexNumber::operator - (const RealNumber& arg)
{
    double a = real_component;
    double b = imaginary_component;
    double c = arg.get_real_component();
    return ComplexNumber((a-c), b);
}

ComplexNumber ComplexNumber::operator * (const RealNumber& arg)
{
    double a = real_component;
    double b = imaginary_component;
    double c = arg.get_real_component();
    return ComplexNumber((a*c), (b*c));
}

ComplexNumber ComplexNumber::operator / (const RealNumber& arg)
{
    double a = real_component;
    double b = imaginary_component;
    double c = arg.get_real_component();
    return ComplexNumber((a/c), (b/c));
}

ComplexNumber ComplexNumber::operator + (const ImaginaryNumber& arg){
    double a = real_component;
    double b = imaginary_component;
    double d = arg.get_imaginary_component();
    return ComplexNumber(a, (b+d));
}

ComplexNumber ComplexNumber::operator - (const ImaginaryNumber& arg)
{
    double a = real_component;
    double b = imaginary_component;
    double d = arg.get_imaginary_component();
    return ComplexNumber(a, (b-d));
}

ComplexNumber ComplexNumber::operator * (const ImaginaryNumber& arg)
{
    double a = real_component;
    double b = imaginary_component;
    double d = arg.get_imaginary_component();
    return ComplexNumber((-1*b*d), (a*d));
}

ComplexNumber ComplexNumber::operator / (const ImaginaryNumber& arg)
{
    double a = real_component;
    double b = imaginary_component;
    double d = arg.get_imaginary_component();
    return ComplexNumber((b/d), (-1 * (a/d)));
}

string ComplexNumber::to_String(){
    /* Do not modify */
    stringstream my_output;
    if (imaginary_component > 0)
        my_output << std::setprecision(3) << real_component << " + " << imaginary_component << 'i';
    else if (imaginary_component < 0)
        my_output << std::setprecision(3) << real_component << " - " << abs(imaginary_component) << 'i';
    else
        my_output << std::setprecision(3) << real_component;
    
    return my_output.str();
}

