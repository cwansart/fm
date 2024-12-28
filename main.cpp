#include <gtk/gtk.h>
#include <iostream>
#include <filesystem>
#include <array>

struct ColDef {
  uint32_t    id;
  const char* title;
};

constexpr uint32_t colSize = 5;
const std::array<ColDef, colSize> columns{{
  { 0, "Type" },
  { 1, "Permissions" },
  { 2, "Size" },
  { 3, "Time" },
  { 4, "Name" },
}};

static std::string perms_to_str(std::filesystem::perms p)
{
  std::string result;
  result += (p & std::filesystem::perms::owner_read)   != std::filesystem::perms::none ? 'r' : '-';
  result += (p & std::filesystem::perms::owner_write)  != std::filesystem::perms::none ? 'w' : '-';
  result += (p & std::filesystem::perms::owner_exec)   != std::filesystem::perms::none ? 'x' : '-';
  result += (p & std::filesystem::perms::group_read)   != std::filesystem::perms::none ? 'r' : '-';
  result += (p & std::filesystem::perms::group_write)  != std::filesystem::perms::none ? 'w' : '-';
  result += (p & std::filesystem::perms::group_exec)   != std::filesystem::perms::none ? 'x' : '-';
  result += (p & std::filesystem::perms::others_read)  != std::filesystem::perms::none ? 'r' : '-';
  result += (p & std::filesystem::perms::others_write) != std::filesystem::perms::none ? 'w' : '-';
  result += (p & std::filesystem::perms::others_exec)  != std::filesystem::perms::none ? 'x' : '-';
  return result;
}

static std::string file_time_to_string(const std::filesystem::file_time_type &file_time)
{
  // Convert file_time_type to system_clock::time_point
  auto sctp = std::chrono::time_point_cast<std::chrono::system_clock::duration>(
      file_time - std::filesystem::file_time_type::clock::now() + std::chrono::system_clock::now());

  // Convert to time_t for easier manipulation
  std::time_t tt = std::chrono::system_clock::to_time_t(sctp);

  // Convert to tm structure
  std::tm tm = *std::localtime(&tt);

  // Format the time as a string
  std::ostringstream oss;
  oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
  return oss.str();
}
 
static GtkTreeModel* create_and_fill_model()
{
  GtkListStore* store = gtk_list_store_new(columns.size(),
                                           G_TYPE_STRING,
                                           G_TYPE_STRING,
                                           G_TYPE_STRING,
                                           G_TYPE_STRING,
                                           G_TYPE_STRING);

  GtkTreeIter iter;

  std::filesystem::path pathToIterate = ".";

  for (const auto& entry: std::filesystem::directory_iterator(pathToIterate))
  {
    std::string type{entry.is_directory() ? "D" : "-"};
    std::string size{entry.is_directory() ? "" : std::to_string(entry.file_size())};
    std::string filePath{entry.path().filename().string()};
    std::string perm{perms_to_str(std::filesystem::status(filePath).permissions())};
    std::string time{file_time_to_string(entry.last_write_time())};
    gtk_list_store_append(store, &iter);
    gtk_list_store_set(store, &iter,
                       columns[0].id, type.c_str(),
                       columns[1].id, perm.c_str(),
                       columns[2].id, size.c_str(),
                       columns[3].id, time.c_str(),
                       columns[4].id, filePath.c_str(),
                       -1);
  }

  return GTK_TREE_MODEL(store);
}

static GtkWidget* create_view_and_model()
{
  GtkWidget *view = gtk_tree_view_new();

  for (const auto& column: columns)
  {
    GtkCellRenderer* renderer = gtk_cell_renderer_text_new();
    gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(view),
                                                -1,
                                                column.title,
                                                renderer,
                                                "text",
                                                column.id,
                                                NULL);
  }

  GtkTreeModel* model = create_and_fill_model();

  gtk_tree_view_set_model(GTK_TREE_VIEW(view), model);

  g_object_unref(model);

  GtkWidget* scrolled_window = gtk_scrolled_window_new(NULL, NULL);
  gtk_container_add(GTK_CONTAINER(scrolled_window), view);

  return scrolled_window;
}

static void activate(GtkApplication* app, gpointer user_data)
{
  // TODO: I have not idea how to initialize the data programatically
  /*
  GtkBuilder* builder = gtk_builder_new();
  GError *error = NULL;
  if (gtk_builder_add_from_file(builder, "fm.ui", &error) == 0)
  {
    g_printerr("Error loading file: %s\n", error->message);
    g_clear_error(&error);
    return;
  }
  
  GtkWidget* window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
  gtk_window_set_application(GTK_WINDOW(window), app);
  gtk_widget_show_all(window);
  g_object_unref(builder);
  */
  
    
  GtkWidget* window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW(window), "FileManager");
  gtk_container_set_border_width(GTK_CONTAINER(window), 10);
  
  GtkWidget* view = create_view_and_model();
  gtk_container_add(GTK_CONTAINER(window), view);
  gtk_widget_show_all(window);
}

int main(int argc, char** argv)
{
  GtkApplication* app = gtk_application_new("de.cwansart.fm", G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
  int status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return status;
}