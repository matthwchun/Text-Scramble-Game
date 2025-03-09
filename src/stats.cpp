#include "stats.h"

ostream& operator << (ostream& out, const Stats& print)
{
  out << "Time taken for test: " << print.timeTaken << endl;
  out << "Accuracy: " << print.accuracy << "%" << endl;
  out << "WPM: " << print.WPM << endl;
  out << "Number of errors: " << print.numErrors << endl;
  out << "Attrition score: " << print.attritionScore << endl;
  return out;
}