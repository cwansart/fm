#include <gtk/gtk.h>
#include <iostream>
#include <filesystem>

enum
{
  COL_TYPE = 0,
  COL_PERM,
  COL_SIZE,
  COL_TIME,
  COL_NAME,
  NUM_COLS
};

std::string perms_to_str(std::filesystem::perms p)
{
  std::string result;

  result += (p & std::filesystem::perms::owner_read) != std::filesystem::perms::none ? 'r' : '-';
  result += (p & std::filesystem::perms::owner_write) != std::filesystem::perms::none ? 'w' : '-';
  result += (p & std::filesystem::perms::owner_exec) != std::filesystem::perms::none ? 'x' : '-';
  result += (p & std::filesystem::perms::group_read) != std::filesystem::perms::none ? 'r' : '-';
  result += (p & std::filesystem::perms::group_write) != std::filesystem::perms::none ? 'w' : '-';
  result += (p & std::filesystem::perms::group_exec) != std::filesystem::perms::none ? 'x' : '-';
  result += (p & std::filesystem::perms::others_read) != std::filesystem::perms::none ? 'r' : '-';
  result += (p & std::filesystem::perms::others_write) != std::filesystem::perms::none ? 'w' : '-';
  result += (p & std::filesystem::perms::others_exec) != std::filesystem::perms::none ? 'x' : '-';

  return result;
}

std::string file_time_to_string(const std::filesystem::file_time_type &file_time)
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

static GtkTreeModel *
create_and_fill_model(void)
{
  GtkListStore *store = gtk_list_store_new(NUM_COLS,
                                           G_TYPE_STRING,
                                           G_TYPE_STRING,
                                           G_TYPE_STRING,
                                           G_TYPE_STRING,
                                           G_TYPE_STRING);

  /* Append a row and fill in some data */
  GtkTreeIter iter;

  std::filesystem::path pathToIterate = ".";

  for (const auto &entry : std::filesystem::directory_iterator(pathToIterate))
  {
    std::string type{entry.is_directory() ? "D" : "-"};
    std::string size{entry.is_directory() ? "" : std::to_string(entry.file_size())};
    std::string filePath{entry.path().filename().string()};
    std::string perm{perms_to_str(std::filesystem::status(filePath).permissions())};
    std::string time{file_time_to_string(entry.last_write_time())};
    gtk_list_store_append(store, &iter);
    gtk_list_store_set(store, &iter,
                       COL_TYPE, type.c_str(),
                       COL_PERM, perm.c_str(),
                       COL_SIZE, size.c_str(),
                       COL_TIME, time.c_str(),
                       COL_NAME, filePath.c_str(),
                       -1);
  }

  return GTK_TREE_MODEL(store);
}

static GtkWidget *
create_view_and_model(void)
{
  GtkWidget *view = gtk_tree_view_new();

  GtkCellRenderer *renderer;

  /* --- Column #1 --- */
  renderer = gtk_cell_renderer_text_new();
  gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(view),
                                              -1,
                                              "Type",
                                              renderer,
                                              "text", COL_TYPE,
                                              NULL);

  /* --- Column #2 --- */
  renderer = gtk_cell_renderer_text_new();
  gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(view),
                                              -1,
                                              "Permissions",
                                              renderer,
                                              "text", COL_PERM,
                                              NULL);

  /* --- Column #3 --- */
  renderer = gtk_cell_renderer_text_new();
  gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(view),
                                              -1,
                                              "Size",
                                              renderer,
                                              "text", COL_SIZE,
                                              NULL);

  /* --- Column #4 --- */
  renderer = gtk_cell_renderer_text_new();
  gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(view),
                                              -1,
                                              "Modification Time",
                                              renderer,
                                              "text", COL_TIME,
                                              NULL);

  /* --- Column #4 --- */
  renderer = gtk_cell_renderer_text_new();
  gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(view),
                                              -1,
                                              "Name",
                                              renderer,
                                              "text", COL_NAME,
                                              NULL);

  GtkTreeModel *model = create_and_fill_model();

  gtk_tree_view_set_model(GTK_TREE_VIEW(view), model);

  /* The tree view has acquired its own reference to the
   *  model, so we can drop ours. That way the model will
   *  be freed automatically when the tree view is destroyed
   */
  g_object_unref(model);

  return view;
}

int main(int argc, char **argv)
{
  gtk_init(&argc, &argv);

  GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  g_signal_connect(window, "destroy", gtk_main_quit, NULL);

  GtkWidget *view = create_view_and_model();

  gtk_container_add(GTK_CONTAINER(window), view);

  gtk_widget_show_all(window);

  gtk_main();

  return 0;
}