#
#  FindPugiXml.cmake
#  svg_rasterizer
#
#  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 25.07.2020.
#  Copyright © 2020 Dmitrii Torkhov. All rights reserved.
#

set(PUGIXML_ROOT ${pugixml_SOURCE_DIR})

set(PUGIXML_INCLUDE_DIRS ${PUGIXML_ROOT}/src)

set(PUGIXML_SRC ${PUGIXML_ROOT}/src/pugixml.cpp)

set_target_properties(pugixml
	PROPERTIES
	EXCLUDE_FROM_ALL True)