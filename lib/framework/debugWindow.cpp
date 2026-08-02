#include "framework/debugWindow.hpp"

#include <cstdarg>

#include "imgui/imgui.h"

void DebugWindow::begin(const char* title) {
  ImGui::Begin(title, nullptr, ImGuiWindowFlags_MenuBar);
}

void DebugWindow::end() { ImGui::End(); }

void DebugWindow::text(const char* fmt, ...) {
  va_list args;
  va_start(args, fmt);
  ImGui::TextV(fmt, args);
  va_end(args);
}

bool DebugWindow::beginTable(const char* label, int columns) {
  return ImGui::BeginTable(label, columns,
                            ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg);
}

void DebugWindow::endTable() { ImGui::EndTable(); }

void DebugWindow::setupColumn(const char* label) {
  ImGui::TableSetupColumn(label);
}

void DebugWindow::headersRow() { ImGui::TableHeadersRow(); }

void DebugWindow::nextRow() { ImGui::TableNextRow(); }

void DebugWindow::nextColumn() { ImGui::TableNextColumn(); }
