#ifndef INCLUDE_FRAMEWORK_DEBUGWINDOW_HPP_
#define INCLUDE_FRAMEWORK_DEBUGWINDOW_HPP_

/**
 * @brief Generic wrapper around the ImGui primitives needed to build a debug
 * window.
 *
 * @details Deliberately has no knowledge of any game types. Callers (e.g.
 * World) use these primitives to draw their own debug content, so that
 * WindowHandler never needs to depend on what the game world looks like.
 */
class DebugWindow {
 public:
  /**
   * @brief Begin the debug window
   *
   * @param title Title of the window
   */
  void begin(const char* title);

  /**
   * @brief End the debug window
   *
   * @details Must be called once for every begin(), after all content has
   * been added.
   */
  void end();

  /**
   * @brief Add a line of printf-formatted text
   *
   * @param fmt Format string
   */
  void text(const char* fmt, ...);

  /**
   * @brief Begin a table
   *
   * @param label Identifier of the table
   * @param columns Number of columns in the table
   * @return true if the table is open and content/endTable() should follow
   * @return false if the table should be skipped entirely
   */
  bool beginTable(const char* label, int columns);

  /**
   * @brief End a table opened with beginTable()
   */
  void endTable();

  /**
   * @brief Declare a column in the current table
   *
   * @param label Header label for the column
   */
  void setupColumn(const char* label);

  /**
   * @brief Draw the header row for the current table
   */
  void headersRow();

  /**
   * @brief Move to the next row in the current table
   */
  void nextRow();

  /**
   * @brief Move to the next column in the current table row
   */
  void nextColumn();
};

#endif /* INCLUDE_FRAMEWORK_DEBUGWINDOW_HPP_ */
