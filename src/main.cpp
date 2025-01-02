#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>

#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

#include "framework/ferd_color.hpp"
#include "framework/geometry/lineObject.hpp"
#include "framework/graphicsFramework.hpp"
#include "game/camera.hpp"
#include "game/line.hpp"
#include "game/physics/kinematics.hpp"
#include "game/train.hpp"
#include "game/waypoint/station.hpp"
#include "game/waypoint/waypoint.hpp"
#include "game/world.hpp"

#define CLOCKS_PER_MSEC (CLOCKS_PER_SEC / 1000)

int main(void) {
  int err;

  spdlog::info("Ferd.");

  GraphicsFramework Framework;
  Framework.Activate();

  const char *vertex_file_path =
      "C:/git/ferd/src/shader/SimpleVertexShader.vertexshader";
  const char *fragment_file_path =
      "C:/git/ferd/src/shader/SimpleFragmentShader.fragmentshader";
  const char *line_vertex_shader_file_path =
      "C:/git/ferd/src/shader/LineVertexShader.vertexshader";
  const char *circle_vertex_shader_file_path =
      "C:/git/ferd/src/shader/CircleVertexShader.vertexshader";
  const char *circle_fragment_file_path =
      "C:/git/ferd/src/shader/CircleFragmentShader.fragmentshader";

  Framework.AddTrainShader(vertex_file_path, fragment_file_path);
  Framework.AddLineShader(line_vertex_shader_file_path, fragment_file_path);
  Framework.AddStationShader(circle_vertex_shader_file_path,
                             circle_fragment_file_path);

  World GameWorld;
  Framework.AddWorld(&GameWorld);

  Waypoint p1({10.000000, 10.000000});
  Waypoint p2({11.163343, 2.701804});
  Waypoint p3({7.070275, -1.573599});
  Waypoint p4({0.000000, 0.000000});
  Waypoint p5({-1.828110, 7.362773});
  Waypoint p6({3.480532, 10.301045});
  Waypoint p7({10.000000, 10.000000});
  Waypoint p8({9.909782, 16.673314});
  Waypoint p9({12.027540, 21.343780});
  Waypoint p10({20.000000, 20.000000});

  Line line1(std::vector<Waypoint *>{&p1, &p2, &p3, &p4, &p5, &p6, &p7, &p8, &p9, &p10}, FERD_COLOR_1);
  //GameWorld.AddLine(&line1);

  Waypoint w1({10.000000, 10.000000});
  Waypoint w2({10.892987, 6.357341});
  Waypoint w3({11.192482, 3.036863});
  Waypoint w4({10.304990, 0.360750});
  Waypoint w5({7.798233, -1.353023});
  Waypoint w6({4.311685, -1.814438});
  Waypoint w7({0.922034, -0.744883});
  Waypoint w8({-1.342986, 2.049525});
  Waypoint w9({-2.039712, 5.778091});
  Waypoint w10({-1.101304, 9.014905});
  Waypoint w11({1.504032, 10.388574});
  Waypoint w12({5.146467, 10.025065});
  Waypoint w13({8.534548, 9.547703});
  Waypoint w14({10.365101, 10.624996});
  Waypoint w15({10.357756, 13.730394});
  Waypoint w16({9.817477, 17.485000});
  Waypoint w17({10.183981, 20.352294});
  Waypoint w18({12.345711, 21.377438});
  Waypoint w19({15.839773, 21.031491});
  Waypoint w20({20.000000, 20.000000});

  Line line2(std::vector<Waypoint *>{&w1, &w2, &w3, &w4, &w5, &w6, &w7, &w8, &w9, &w10, &w11, &w12, &w13, &w14, &w15, &w16, &w17, &w18, &w19, &w20}, FERD_COLOR_2);
  //GameWorld.AddLine(&line2);

  Waypoint wp1({10.000000, 10.000000});
  Waypoint wp2({10.378849, 8.569850});
  Waypoint wp3({10.723096, 7.158483});
  Waypoint wp4({10.998142, 5.784682});
  Waypoint wp5({11.169385, 4.467232});
  Waypoint wp6({11.202223, 3.224915});
  Waypoint wp7({11.062057, 2.076516});
  Waypoint wp8({10.714286, 1.040816});
  Waypoint wp9({10.124307, 0.136601});
  Waypoint wp10({9.266920, -0.617593});
  Waypoint wp11({8.179405, -1.204857});
  Waypoint wp12({6.924535, -1.608948});
  Waypoint wp13({5.565156, -1.813624});
  Waypoint wp14({4.164114, -1.802644});
  Waypoint wp15({2.784257, -1.559767});
  Waypoint wp16({1.488430, -1.068751});
  Waypoint wp17({0.339481, -0.313356});
  Waypoint wp18({-0.602673, 0.717722});
  Waypoint wp19({-1.312166, 1.978385});
  Waypoint wp20({-1.785101, 3.385502});
  Waypoint wp21({-2.017948, 4.855325});
  Waypoint wp22({-2.007176, 6.304104});
  Waypoint wp23({-1.749255, 7.648092});
  Waypoint wp24({-1.240653, 8.803540});
  Waypoint wp25({-0.477839, 9.686700});
  Waypoint wp26({0.541039, 10.217618});
  Waypoint wp27({1.779263, 10.403639});
  Waypoint wp28({3.161539, 10.339403});
  Waypoint wp29({4.610899, 10.123346});
  Waypoint wp30({6.050373, 9.853905});
  Waypoint wp31({7.402992, 9.629516});
  Waypoint wp32({8.591786, 9.548615});
  Waypoint wp33({9.539785, 9.709638});
  Waypoint wp34({10.171014, 10.209861});
  Waypoint wp35({10.469127, 11.076885});
  Waypoint wp36({10.510204, 12.230321});
  Waypoint wp37({10.378276, 13.580487});
  Waypoint wp38({10.157375, 15.037705});
  Waypoint wp39({9.931530, 16.512294});
  Waypoint wp40({9.784774, 17.914574});
  Waypoint wp41({9.801136, 19.154865});
  Waypoint wp42({10.064553, 20.143587});
  Waypoint wp43({10.626822, 20.825073});
  Waypoint wp44({11.460956, 21.226785});
  Waypoint wp45({12.528117, 21.388691});
  Waypoint wp46({13.789466, 21.350758});
  Waypoint wp47({15.206167, 21.152956});
  Waypoint wp48({16.739382, 20.835250});
  Waypoint wp49({18.350272, 20.437609});
  Waypoint wp50({20.000000, 20.000000});

  Line line3(std::vector<Waypoint *>{&wp1, &wp2, &wp3, &wp4, &wp5, &wp6, &wp7, &wp8, &wp9, &wp10,
                       &wp11, &wp12, &wp13, &wp14, &wp15, &wp16, &wp17, &wp18, &wp19, &wp20,
                       &wp21, &wp22, &wp23, &wp24, &wp25, &wp26, &wp27, &wp28, &wp29, &wp30,
                       &wp31, &wp32, &wp33, &wp34, &wp35, &wp36, &wp37, &wp38, &wp39, &wp40,
                       &wp41, &wp42, &wp43, &wp44, &wp45, &wp46, &wp47, &wp48, &wp49, &wp50}, FERD_COLOR_3);
  //GameWorld.AddLine(&line3);

  Waypoint point1({10.000000, 10.000000});
Waypoint point2({10.189666, 9.290978});
Waypoint point3({10.375137, 8.584233});
Waypoint point4({10.552216, 7.882044});
Waypoint point5({10.716710, 7.186686});
Waypoint point6({10.864422, 6.500439});
Waypoint point7({10.991158, 5.825579});
Waypoint point8({11.092721, 5.164385});
Waypoint point9({11.164916, 4.519132});
Waypoint point10({11.203549, 3.892100});
Waypoint point11({11.204423, 3.285565});
Waypoint point12({11.163343, 2.701804});
Waypoint point13({11.076114, 2.143097});
Waypoint point14({10.938541, 1.611719});
Waypoint point15({10.746427, 1.109948});
Waypoint point16({10.495579, 0.640062});
Waypoint point17({10.181800, 0.204339});
Waypoint point18({9.801141, -0.194951});
Waypoint point19({9.355314, -0.555684});
Waypoint point20({8.851694, -0.875885});
Waypoint point21({8.297901, -1.153584});
Waypoint point22({7.701555, -1.386812});
Waypoint point23({7.070275, -1.573599});
Waypoint point24({6.411683, -1.711977});
Waypoint point25({5.733399, -1.799977});
Waypoint point26({5.043042, -1.835628});
Waypoint point27({4.348233, -1.816962});
Waypoint point28({3.656591, -1.742010});
Waypoint point29({2.975738, -1.608802});
Waypoint point30({2.313293, -1.415369});
Waypoint point31({1.676877, -1.159741});
Waypoint point32({1.074109, -0.839950});
Waypoint point33({0.512610, -0.454026});
Waypoint point34({0.000000, 0.000000});
Waypoint point35({-0.457300, 0.522077});
Waypoint point36({-0.857662, 1.104070});
Waypoint point37({-1.200659, 1.735826});
Waypoint point38({-1.485862, 2.407190});
Waypoint point39({-1.712844, 3.108007});
Waypoint point40({-1.881177, 3.828122});
Waypoint point41({-1.990431, 4.557382});
Waypoint point42({-2.040180, 5.285632});
Waypoint point43({-2.029995, 6.002716});
Waypoint point44({-1.959448, 6.698482});
Waypoint point45({-1.828110, 7.362773});
Waypoint point46({-1.635555, 7.985436});
Waypoint point47({-1.381353, 8.556316});
Waypoint point48({-1.065076, 9.065259});
Waypoint point49({-0.686297, 9.502109});
Waypoint point50({-0.244588, 9.856714});
Waypoint point51({0.260277, 10.119377});
Waypoint point52({0.823846, 10.290990});
Waypoint point53({1.436988, 10.383028});
Waypoint point54({2.090371, 10.407426});
Waypoint point55({2.774663, 10.376120});
Waypoint point56({3.480532, 10.301045});
Waypoint point57({4.198644, 10.194136});
Waypoint point58({4.919667, 10.067329});
Waypoint point59({5.634269, 9.932560});
Waypoint point60({6.333116, 9.801763});
Waypoint point61({7.006877, 9.686875});
Waypoint point62({7.646219, 9.599830});
Waypoint point63({8.241809, 9.552565});
Waypoint point64({8.784315, 9.557013});
Waypoint point65({9.264404, 9.625112});
Waypoint point66({9.672743, 9.768796});
Waypoint point67({10.000000, 10.000000});
Waypoint point68({10.240096, 10.326859});
Waypoint point69({10.399966, 10.742300});
Waypoint point70({10.489799, 11.235450});
Waypoint point71({10.519784, 11.795435});
Waypoint point72({10.500110, 12.411382});
Waypoint point73({10.440964, 13.072415});
Waypoint point74({10.352536, 13.767662});
Waypoint point75({10.245016, 14.486250});
Waypoint point76({10.128590, 15.217303});
Waypoint point77({10.013449, 15.949949});
Waypoint point78({9.909782, 16.673314});
Waypoint point79({9.827776, 17.376524});
Waypoint point80({9.777620, 18.048706});
Waypoint point81({9.769504, 18.678985});
Waypoint point82({9.813616, 19.256487});
Waypoint point83({9.920145, 19.770340});
Waypoint point84({10.098969, 20.209997});
Waypoint point85({10.352829, 20.572444});
Waypoint point86({10.677325, 20.862200});
Waypoint point87({11.067748, 21.084110});
Waypoint point88({11.519390, 21.243021});
Waypoint point89({12.027540, 21.343780});
Waypoint point90({12.587491, 21.391231});
Waypoint point91({13.194533, 21.390221});
Waypoint point92({13.843956, 21.345597});
Waypoint point93({14.531053, 21.262204});
Waypoint point94({15.251113, 21.144888});
Waypoint point95({15.999427, 20.998496});
Waypoint point96({16.771287, 20.827873});
Waypoint point97({17.561983, 20.637866});
Waypoint point98({18.366807, 20.433321});
Waypoint point99({19.181049, 20.219084});
Waypoint point100({20.000000, 20.000000});

  Line line4(std::vector<Waypoint *>{&point1, &point2, &point3, &point4, &point5, &point6, &point7, &point8, &point9, &point10,
                      &point11, &point12, &point13, &point14, &point15, &point16, &point17, &point18, &point19, &point20,
                      &point21, &point22, &point23, &point24, &point25, &point26, &point27, &point28, &point29, &point30,
                      &point31, &point32, &point33, &point34, &point35, &point36, &point37, &point38, &point39, &point40,
                      &point41, &point42, &point43, &point44, &point45, &point46, &point47, &point48, &point49, &point50,
                      &point51, &point52, &point53, &point54, &point55, &point56, &point57, &point58, &point59, &point60,
                      &point61, &point62, &point63, &point64, &point65, &point66, &point67, &point68, &point69, &point70,
                      &point71, &point72, &point73, &point74, &point75, &point76, &point77, &point78, &point79, &point80,
                      &point81, &point82, &point83, &point84, &point85, &point86, &point87, &point88, &point89, &point90,
                      &point91, &point92, &point93, &point94, &point95, &point96, &point97, &point98, &point99, &point100}, FERD_COLOR_4);
  GameWorld.AddLine(&line4);

  spdlog::info("Starting render loop");

  Camera GameCamera;
  Framework.addCamera(&GameCamera);

  /* Loop until the user closes the window */
  clock_t lastFrame = clock();
  while (Framework.isRunning()) {
    clock_t curr_frame = clock();
    float delta_time_ms = (curr_frame - lastFrame) / CLOCKS_PER_MSEC;
    Framework.Update(delta_time_ms);
    spdlog::debug("Time since last frame: {0} ms ({1:.2f} FPS)", delta_time_ms,
                  (1 / delta_time_ms) * 1000);
    Framework.Render();

    /* Swap front and back buffers */
    Framework.swapBuffers();
    lastFrame = curr_frame;
  }

  spdlog::info("Terminating");
  Framework.terminate();

  return 0;
}
