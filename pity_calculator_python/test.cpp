#include <vector>
#include <iostream>

struct PeakData {
  std::vector<int> pos, peaks;
};

#include <vector>

PeakData pick_peaks(const std::vector<int> &v) {
  
  PeakData result;

  for(int i: result.peaks) {std::cout << i; };

  for(size_t i{ 1 }; i < (v.size() - 2); i++) {
    if(v[i] > v[i-1] && v[i] > v[i+1]) {
      result.peaks.push_back( v[i] );
      result.pos.push_back( i );
    }
  }
  
 return result;
}

int main() {
  PeakData x = pick_peaks(std::vector<int> {3, 2, 3, 6, 4, 1, 2, 3, 2, 1, 2, 3});

  int num = x.peaks.size(); 
  for(int i{0}; i <= num; i++) {
  std::cout << x.peaks[i];
  std::cout << x.pos[i];
}
  return 0;
}