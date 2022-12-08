#include "Node.h"

Node::Node(Train& _train)
	: train(_train), next(nullptr) {
}