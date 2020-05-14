PROJECT_HOME      = File.expand_path(File.dirname(__FILE__))
PROJECT_NAME      = "ilearn"
SRC_DIR           = "#{PROJECT_HOME}/src"
BIN_DIR           = "#{PROJECT_HOME}/bin"
EXE_FILE          = "#{BIN_DIR}/#{PROJECT_NAME}"
BUILD_DIR         = "#{PROJECT_HOME}/build"
OBJ_FILES_DIR     = "#{BUILD_DIR}/objects"
INCLUDE_DIRS      = %w(/usr/local/boost_1_59_0/ /usr/local/include/libgpio/)
INCLUDE_OPTION    = INCLUDE_DIRS.map{|i_dir| "-I#{i_dir}"}.join(' ')
#LIB_DIRS          = %w(/usr/local/lib/ /usr/local/lib/libgpio/)
LIB_DIRS          = %w(/tmp/boost_for_raspberry/lib/ /usr/local/lib/libgpio/)
LIB_FILES         = %w(boost_program_options gpio)
LIB_OPTIONS       = "#{LIB_DIRS.map{|l_dir| "-L#{l_dir}"}.join(' ')} #{LIB_FILES.map{|l_dir| "-l #{l_dir}"}.join(' ')}"
COMPILE_COMMANDS  = {
  cpp: ->(build_file, target_file) {
    #"g++ -Wall -O0 -DNDEBUG -std=c++14 #{INCLUDE_OPTION} -o #{build_file}.o -c #{target_file}"
    "arm-linux-gnueabihf-g++ -Wall -O0 -DNDEBUG -std=c++14 #{INCLUDE_OPTION} -o #{build_file}.o -c #{target_file}"
  }
}
LINK_COMMAND      = ->(exe_file, obj_files) {
  #"g++ -shared -Wall -O0 -DNDEBUG -std=c++14 #{LIB_OPTIONS} -Wl,-rpath-link=#{LIB_DIRS} -lbcm_host -o #{so_file}.so #{obj_files}"
  "arm-linux-gnueabihf-g++ -Wall -O0 -DNDEBUG -std=c++14 -o #{exe_file} #{obj_files} #{LIB_OPTIONS}"
}

task :default => ['build']

def get_match_files_recursion(path, &block)

  files = []

  Dir.each_child(path) do |f|

    file = "#{path}/#{f}"

    case File.ftype(file).to_sym
    when :directory
      files.concat(get_match_files_recursion(file, &block))
    when :file
      files << file if yield(file)
    else
    end
  end

  return files
end

desc "build to all"
task :build do |task, args|
  Rake::Task['build:clean'].execute
  Rake::Task['build:compile'].execute(args)
  Rake::Task['build:link'].execute
end

namespace :build do

  desc "compile"
  task :compile do |task, args|

    FileUtils.mkdir_p(OBJ_FILES_DIR) unless Dir.exists?(OBJ_FILES_DIR)

    COMPILE_COMMANDS.each do |suffix, command|
      func = ->(f){ File.fnmatch("*.#{suffix}", f) }
      target_files = get_match_files_recursion(SRC_DIR, &func)

      if args['all'].nil? || !!!args['all']
        #todo timestamp で差分のみ
      end

      target_files.each do |target|
        basename = File.basename(target, ".#{suffix}")
        sh command.call("#{OBJ_FILES_DIR}/#{basename}", target)
      end
    end
  end

  desc "link"
  task :link do
    FileUtils.mkdir_p(BIN_DIR) unless Dir.exists?(BIN_DIR)
    obj_files = get_match_files_recursion(OBJ_FILES_DIR){|f| File.fnmatch("*.o", f)}.join(' ')
    sh LINK_COMMAND.call(EXE_FILE, obj_files)
  end

  desc "rm build dir"
  task :clean do
    sh "rm -rf #{BUILD_DIR}" if Dir.exists?(BUILD_DIR)
  end
end
