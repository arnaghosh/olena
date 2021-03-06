#include <mln/core/alias/box2d.hh>
int main()
{
  using namespace mln;

// \{
  box2d b(2,3);

  // The bbox can be retrieved in constant time.
  std::cout << b.bbox() << std::endl;

  // nsites can be retrieved in constant time.
  std::cout << "nsites = " << b.nsites() << std::endl;
// \}
}
