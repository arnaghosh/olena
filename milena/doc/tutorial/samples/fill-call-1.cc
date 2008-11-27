#include <mln/essential/2d.hh>
int main()
{
  using namespace mln;

  // \{
  image2d<char> imga(5, 5);
  // \}

  // \{
  level::fill(imga, 'a');
  // \}

  // \{
  level::fill((imga | box2d(1,2)).rw(), 'a');
  // \}

}
